// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainingPlanController.h"
#include "Engine.h"
//#include "TrainingPlanBlueprintLibrary.h"

// Sets default values for this component's properties
UTrainingPlanController::UTrainingPlanController() : TimeMultiplier(1.0f),
SecondsHowOftenCheckPlayerAverage(5.0f), SecondsToFirstCheck(180), SecondsToRemember(180), Threshold(0.4f), DisplayLogs(true),
averageTotal(0), movingAverage(0), currentMove(0), currentSet(0),
currentTime(0), timerTotalTime(0), totalTimeSinceBeginning(0), isWorkoutChanged(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


void UTrainingPlanController::SetTrainingPlan(FAerobicTrainingUnitResponse trainingPlan)
{
	controlledTraining = trainingPlan;
}

void UTrainingPlanController::StartControllingTraining()
{
	if (DisplayLogs)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::StartControllingTraining - Starting: %d, %d"), currentMove, currentSet);
	}
	currentMove = currentSet = 0;
	currentAverageWattsCheckStatus = EPlayerAverageWattsResult::IsInExpectedLimit;
	if (CheckIndicesCorrectness())
	{
		trainingPhase = controlledTraining.aerobicSets[currentSet].trainingPhase;
		SetComponentTickEnabled(true);
		OnTrainingIntervalStarted.Broadcast(currentMove, currentSet);
	}
}


void UTrainingPlanController::AddMeasurment(float btp)
{
	if (trainingPhase != ETrainingPhase::Training) return;
	if (currentMove != lastMove) {
		movingAverage = 0;
		measurments.Empty();
	}
	lastMove = currentMove;
	//if ((currentMove & 1) == 1) // assuming we start with power interval
	//	return;

	float lastRestingIntervalDuraion = currentMove == 0 ? 0 :
		controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove - 1].durationInSeconds;
	float time = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - lastRestingIntervalDuraion / TimeMultiplier;
	FTimeEvent timeEvent;
	timeEvent.Btp = btp;
	timeEvent.TimeStamp = time * TimeMultiplier;
	averageTotal = averageTotal + (btp - averageTotal) / (float)(++currentSamples);
	float sumOfRemovedSamples;
	RemoveOldSamples(sumOfRemovedSamples);
	movingAverage = (measurments.Num() * movingAverage + btp) / (measurments.Num() + 1);
	measurments.Add(timeEvent);
	//UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::UTrainingPlanController::AddMeasurment - movingAverage: %d"), movingAverage);
	//Broadcast on average updated;
	OnTimeAverageUpdated.Broadcast(movingAverage, averageTotal);
	//Calculate moving average only during interval
}

// Called when the game starts
void UTrainingPlanController::BeginPlay()
{
	Super::BeginPlay();
	SecondsToFirstCheck /= TimeMultiplier;
	timeToChangeWorkout = 30;
	//PerformTests();
	// ...

}

void UTrainingPlanController::PerformTests()
{
	TArray<FTimeEvent> tab1;
	TArray<float> tab1_f = { 7,3,2,8 };

	TArray<FTimeEvent> tab2;
	TArray<float> tab2_f = { 1,1,2,3,1,4,5,6,7,8,1,2,3 };

	for (int i = 0; i < tab1_f.Num(); i++)
	{
		FTimeEvent e;
		e.Btp = tab1_f[i];
		e.TimeStamp = i;
		tab1.Add(e);
	}

	for (int i = 0; i < tab2_f.Num(); i++)
	{
		FTimeEvent e;
		e.Btp = tab2_f[i];
		e.TimeStamp = i;
		tab2.Add(e);
	}

	SecondsToRemember = 2;
	TestMethod(tab1);

	SecondsToRemember = 3;
	TestMethod(tab2);
}

void UTrainingPlanController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	currentTime += (DeltaTime * TimeMultiplier);
	totalTimeSinceBeginning += currentTime;
	auto currentInterval = controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove];
	if (currentTime >= currentInterval.durationInSeconds)
	{
		currentTime = 0;
		UpdateCurrentTrainigPlanProgress();
	}
	else {
		CheckIntervalCorrectness();
	}

}

void UTrainingPlanController::CheckIntervalCorrectness()
{
	float timerElapsed = GetWorld()->GetTimerManager().GetTimerElapsed(checkIntervalCorrectnessTimerHandle);
	timerTotalTime += timerElapsed;
	if (timerTotalTime < SecondsToFirstCheck) return;

	EWorkoutChange ChangeType;

	FString result = "";
	auto currentInterval = controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove];
	float vMax = currentInterval.valueMax;
	float vMin = currentInterval.valueMin;
	if (movingAverage >= (1.0f + Threshold) * vMax)
	{
		if (timeToChangeWorkout == 0)
		{
			controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMax = vMax + ((vMax / 100)*wattsPercentageChange);
			controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMin = vMin + ((vMin / 100)*wattsPercentageChange);
			UE_LOG(LogTemp, Error, TEXT("zmiana - vMax %f | vMin %f"), controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMax, controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMin);
			ChangeType = EWorkoutChange::ScaledUp;
			isWorkoutChanged = false;
			timeToChangeWorkout = 60;
		}
		if (isWorkoutChanged)
		{
			timeToChangeWorkout--;
			//StopTrainingPlan(false);
			//return;
		}
		isWorkoutChanged = true;
		wattsPercentageChange = controlledTraining.powerChangeScenarioPercent;
		currentAverageWattsCheckStatus = EPlayerAverageWattsResult::BetterThanExpected;
		result = "BetterThanExpected";
	}
	else if (movingAverage <= (1.0f - Threshold) * vMin)
	{
		if (timeToChangeWorkout == 0)
		{
			controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMax = vMax - ((vMax / 100)*wattsPercentageChange);
			controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMin = vMin - ((vMin / 100)*wattsPercentageChange);
			UE_LOG(LogTemp, Error, TEXT("zmiana - vMax %f | vMin %f"), controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMax, controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove].valueMin);
			ChangeType = EWorkoutChange::ScaledDown;
			isWorkoutChanged = false;
			timeToChangeWorkout = 60;
		}
		if (isWorkoutChanged)
		{
			timeToChangeWorkout--;
			//StopTrainingPlan(false);
			//return;
		}
		isWorkoutChanged = true;
		wattsPercentageChange = -controlledTraining.powerChangeScenarioPercent;
		currentAverageWattsCheckStatus = EPlayerAverageWattsResult::WorseThanExpected;
		result = "WorseThanExpected";
	}
	else
	{
		currentAverageWattsCheckStatus = EPlayerAverageWattsResult::IsInExpectedLimit;
		result = "IsInExpectedLimit";
		timeToChangeWorkout = 60;
		isWorkoutChanged = false;
	}
	if (DisplayLogs)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::CheckIntervalCorrectness vMax: %f, vMin: %f"), vMax, vMin);
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::CheckIntervalCorrectness %f, %f"), timerElapsed, timerTotalTime);
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::CheckIntervalCorrectness - %s"), *result);
	}
	if (isWorkoutChanged && timeToChangeWorkout == 60)
	{
		FWorkoutChangeInfo changeInfo;
		changeInfo.workoutChangeType = ChangeType;
		changeInfo.set = currentSet;
		changeInfo.move = currentMove;
		changeInfo.timeSinceBeginningOfWorkout = totalTimeSinceBeginning;
		changeInfo.timeRelativeToInterval = currentTime;
		OnWorkoutChanged.Broadcast(changeInfo);
		//ResetRemainingTraining();
	}
	OnPlayerWattsStatusCheck.Broadcast(currentAverageWattsCheckStatus);
	
}

void UTrainingPlanController::ResetRemainingTraining()
{
	if (DisplayLogs)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::ResetRemainingTraining"));
	}
	measurments.Reset();
	movingAverage = 0;
	timerTotalTime = 0;
	currentTime = 0;
}

int UTrainingPlanController::RemoveOldSamples(float& sumOfRemovedSamples)
{
	if (measurments.Num() == 0) return 0;
	//UE_LOG(LogTemp, Warning, TEXT("RemoveOldSamples"));
	auto latest = measurments[measurments.Num() - 1].TimeStamp;
	auto oldest = measurments[0].TimeStamp;
	if (latest - oldest <= SecondsToRemember)
		return 0;
	int elemsToRemove = 0;
	int count = measurments.Num();
	while (latest - oldest > SecondsToRemember)
	{
		movingAverage = ((movingAverage * count) - measurments[elemsToRemove].Btp) / (count - 1);
		count--;
		elemsToRemove++;
		oldest = measurments[elemsToRemove].TimeStamp;
	}
	measurments.RemoveAt(0, elemsToRemove, true);
	return elemsToRemove;
}

void UTrainingPlanController::UpdateCurrentTrainigPlanProgress()
{
	if (DisplayLogs)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::UpdateCurrentTrainigPlanProgress - INTERVAL FINISHED: move: %d, set: %d"), currentMove, currentSet);
	}
	bool isWorkoutFinished = UpdateTrainingIndices();
	if (isWorkoutFinished)
	{
		StopTrainingPlan(true);
		return;
	}

	//to be sure, check for correctness
	if (!CheckIndicesCorrectness())
	{
		if (DisplayLogs)
		{
			UE_LOG(LogTemp, Error, TEXT("UTrainingPlanController::UpdateCurrentTrainigPlanProgress - something went wrong"));
		}
		SetComponentTickEnabled(false);
		return;
	}

	OnTrainingIntervalStarted.Broadcast(currentMove, currentSet);
	trainingPhase = controlledTraining.aerobicSets[currentSet].trainingPhase;
	UpdateTimerHandler();

	if (DisplayLogs)
	{
		auto currentInterval = controlledTraining.aerobicSets[currentSet].aerobicMoves[currentMove];
		//currentExpectedPowerInWatts = currentInterval.expectedPowerInWatts;
		UE_LOG(LogTemp, Warning, TEXT("UTrainingPlanController::UpdateCurrentTrainigPlanProgress - Starting Interval: move: %d, set: %d"), currentMove, currentSet);
	}
}

bool UTrainingPlanController::UpdateTrainingIndices()
{
	bool isWorkoutFinished = false;
	auto sets = controlledTraining.aerobicSets;
	OnTrainingIntervalFinished.Broadcast(currentMove, currentSet);
	currentMove++;

	if (currentMove >= sets[currentSet].aerobicMoves.Num())
	{
		currentMove = 0;
		currentSet++;
		if (currentSet >= controlledTraining.aerobicSets.Num())
			isWorkoutFinished = true;
	}
	return isWorkoutFinished;
}

void UTrainingPlanController::UpdateTimerHandler()
{
	if (trainingPhase != ETrainingPhase::Training)
	{
		GetWorld()->GetTimerManager().ClearTimer(checkIntervalCorrectnessTimerHandle);
		return;
	}

	if (currentMove == 0) // if first interval, initialize the timer
	{
		GetWorld()->GetTimerManager().SetTimer(checkIntervalCorrectnessTimerHandle, this,
			&UTrainingPlanController::CheckIntervalCorrectness, SecondsHowOftenCheckPlayerAverage, true);
		return;
	}
	if ((currentMove & 1) == 1) // resting intervals
		GetWorld()->GetTimerManager().PauseTimer(checkIntervalCorrectnessTimerHandle);
	else GetWorld()->GetTimerManager().UnPauseTimer(checkIntervalCorrectnessTimerHandle);

}

void UTrainingPlanController::StopTrainingPlan(bool success)
{
	currentSet = 0;
	timerTotalTime = 0;
	currentTime = 0;
	SetComponentTickEnabled(false);
	GetWorld()->GetTimerManager().ClearTimer(checkIntervalCorrectnessTimerHandle);
	if(success) OnWorkoutSucceeded.Broadcast();
	else OnWorkoutFailed.Broadcast();
}

void UTrainingPlanController::TestMethod(TArray<FTimeEvent> elems)
{
	for (int i = 0; i < elems.Num(); i++)
	{
		AddMeasurment(elems[i]);
	}
	currentSamples = 0;
	averageTotal = 0;
	movingAverage = 0;
	measurments.Empty();
	UE_LOG(LogTemp, Warning, TEXT("-----------------------------"));
}

void UTrainingPlanController::AddMeasurment(FTimeEvent timevent)
{
	measurments.Add(timevent);
	averageTotal = averageTotal + (timevent.Btp - averageTotal) / (float)(++currentSamples);
	float sumOfRemovedSamples;
	movingAverage = ((measurments.Num() - 1) * movingAverage + timevent.Btp) / (measurments.Num());
	RemoveOldSamples(sumOfRemovedSamples);
	if (DisplayLogs)
	{
		UE_LOG(LogTemp, Warning, TEXT("timeEvent: %f, %f, tot: %f, mov: %f"), timevent.Btp, timevent.TimeStamp, averageTotal, movingAverage);
	}
}

bool UTrainingPlanController::CheckIndicesCorrectness()
{
	auto areIndicesOk = currentSet < controlledTraining.aerobicSets.Num() &&
		currentMove < controlledTraining.aerobicSets[currentSet].aerobicMoves.Num();
	return areIndicesOk;
}
