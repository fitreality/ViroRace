// Fill out your copyright notice in the Description page of Project Settings.


#include "NetMovementComponent.h"
#include <Runtime/Engine/Classes/GameFramework/Pawn.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include <Runtime/Engine/Classes/GameFramework/GameStateBase.h>
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

// Sets default values for this component's properties
UNetMovementComponent::UNetMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bReplicates = true;
	// ...
}

void UNetMovementComponent::Initialize(USceneComponent* sceneComponent)
{
	owner = Cast<APawn>(GetOwner());
	if (!owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn should be owner of this component"));
		return;
	}
	if (owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNetMovementComponent::BeginPlay owner's name: %s, local role: %d"), *owner->GetName(), owner->GetLocalRole());
	}

	auto role = owner->GetLocalRole();
	if (role == ROLE_SimulatedProxy)
		SetComponentTickEnabled(true);

	moveDuration = 0.25f;
	gameState = UGameplayStatics::GetGameState(GetWorld());
	auto transform = owner->GetActorTransform();
	inteprolatedPosition = transform.GetLocation();
	componentToMove = sceneComponent ? sceneComponent : owner->GetRootComponent();
	
}


// Called when the game starts
void UNetMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UNetMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float now = gameState->GetServerWorldTimeSeconds();
	float render_timestamp = now - moveDuration;

	//UE_LOG(LogTemp, Warning, TEXT("czas delta:  %f"), DeltaTime);

	while (queue.Num() >= 2 && queue[1].serverTime <= render_timestamp)
	{
		queue.RemoveAt(0);
	}

	if (queue.Num() >= 2 && queue[0].serverTime <= render_timestamp && render_timestamp <= queue[1].serverTime) {
		FVector x0 = queue[0].location;
		FVector x1 = queue[1].location;
		FRotator r0 = queue[0].rotator;
		FRotator r1 = queue[1].rotator;
		float t0 = queue[0].serverTime;
		float t1 = queue[1].serverTime;
		float v = (render_timestamp - t0) / (t1 - t0);
		auto pawnLocation = x0 + (x1 - x0) * v;
		inteprolatedPosition = FMath::Lerp(x0, x1, v);
		interpolatedRotator = FMath::Lerp(r0, r1, v);
		//UE_LOG(LogTemp, Warning, TEXT("r: %f, t0: %f, t1: %f, name: %s, position: %f"), render_timestamp, t0, t1, *owner->GetName(), inteprolatedPosition.X);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ELSE"));
	}

	if (queue.Num() == 1 && queue[0].serverTime <= render_timestamp)
	{
		//clientState.Position = Vector2.Lerp(clientState.Position, interpolationBuffer.First.Value.Position, interpolationCoeff);
		inteprolatedPosition = queue[0].location;
		//interpolationBuffer.RemoveFirst();
	}

	


	if (componentToMove)
	{
		
		//componentToMove->SetWorldLocation(inteprolatedPosition);
		componentToMove->SetWorldRotation(interpolatedRotator);
		
		//componentToMove->SetWorldLocation(latestNetTransform.location);

		TimeTick = GetWorld()->GetTimeSeconds();
		DeltaTimeTick = TimeTick - LastTimeTick;
		LastTimeTick = TimeTick;



		VeloProxy = FMath::Lerp(LastVeloProxy, VeloProxy, 0.2f);
		LocNetRep = LocNetRep + (VeloNetRep * DeltaTimeTick);
		LocProxy = LocProxy + (VeloProxy * DeltaTimeTick);
		LocProxy = FMath::Lerp(LocProxy, LocNetRep, 0.2f);

		LastVeloProxy = VeloProxy = (LocProxy - LastLocProxy) / DeltaTimeTick;
		LastLocProxy = LocProxy;
		componentToMove->SetWorldLocation(LocNetRep);
		
	}
}

void UNetMovementComponent::ReplicateMovement(FTransform pawnTransform)
{
	if (!componentToMove)
	{
		UE_LOG(LogTemp, Error, TEXT("Component to move not initialized. Did you forget to call Initialize function on NetMovememnt Componennt???"));
		return;
	}
	FPawnNetTransform transform;
	transform.location = pawnTransform.GetLocation();
	transform.rotator = pawnTransform.GetRotation().Rotator();
	transform.serverTime = gameState->GetServerWorldTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("czas RepMove:  %f, nazwa: %s"), gameState->GetServerWorldTimeSeconds(), *owner->GetName());
	SendCurrentTransform(transform);
}


bool UNetMovementComponent::SendCurrentTransform_Validate(FPawnNetTransform pawnOptimizedTransform)
{
	return true;
}

void UNetMovementComponent::SendCurrentTransform_Implementation(FPawnNetTransform pawnOptimizedTransform)
{
	if (!componentToMove)
	{
		UE_LOG(LogTemp, Error, TEXT("Component to move not initialized. Did you forget to call Initialize function on NetMovememnt Componennt???"));
		return;
	}
	latestNetTransform = pawnOptimizedTransform;

	//auto robo = componentToMove->GetComponentLocation();

	//componentToMove->SetWorldLocation(latestNetTransform.location);
	//componentToMove->SetWorldRotation(latestNetTransform.rotator);
	//UE_LOG(LogTemp, Warning, TEXT("pX: %f, pY: %f, lX: %f, lY: %f"), latestNetTransform.location.X, latestNetTransform.location.Y, robo.X, robo.Y);
	//UE_LOG(LogTemp, Warning, TEXT("czas World:  %f, name:  %s"), gameState->GetServerWorldTimeSeconds(), *owner->GetName());
	
}

void UNetMovementComponent::OnRep_LatestNetTransform()
{

	//roboczas = gameState->GetServerWorldTimeSeconds();
	//roboczas = latestNetTransform.serverTime;
	queue.Add(latestNetTransform);

	TimeRep = GetWorld()->GetTimeSeconds();
	DeltaTimeRep = TimeRep - LastTimeRep;
	LastTimeRep = TimeRep;	
	
	LocNetRep = latestNetTransform.location;	
	VeloNetRep = (LocNetRep - LastLocNetRep) / DeltaTimeRep;
	LastLocNetRep = LocNetRep;	
	
	//UE_LOG(LogTemp, Warning, TEXT("dodaj do kolejki: %f, imie: %s, velo: %f, droga: %f"), deltaroboczas, *owner->GetName(), VeloNet.Size(), Droga.Size() );	

}

void UNetMovementComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UNetMovementComponent, latestNetTransform, COND_SimulatedOnly);
}