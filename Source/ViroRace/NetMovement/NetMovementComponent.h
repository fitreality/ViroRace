// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Runtime/Core/Public/Containers/Queue.h>
#include "NetMovementComponent.generated.h"

class APawn;
class AGameStateBase;
class USceneComponent;

USTRUCT(BlueprintType)
struct FPawnNetTransform
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator rotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float serverTime;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIRORACE_API UNetMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetMovementComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize(USceneComponent* sceneComponent = nullptr);

	UFUNCTION(BlueprintCallable)
	void ReplicateMovement(FTransform pawnTransform);

protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, WithValidation, unreliable)
	void SendCurrentTransform(FPawnNetTransform pawnOptimizedTransform);
	bool SendCurrentTransform_Validate(FPawnNetTransform pawnOptimizedTransform);
	void SendCurrentTransform_Implementation(FPawnNetTransform pawnOptimizedTransform);

	UFUNCTION()
	virtual void OnRep_LatestNetTransform();

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_LatestNetTransform)
	FPawnNetTransform latestNetTransform;

	UPROPERTY()
	USceneComponent* componentToMove;

private:
	APawn* owner;
	FVector inteprolatedPosition;
	FRotator interpolatedRotator;
	AGameStateBase* gameState;

	float moveDuration;
	TArray<FPawnNetTransform> queue;

	float TimeRep;
	float LastTimeRep;
	float DeltaTimeRep;
	
	float TimeTick;
	float LastTimeTick;
	float DeltaTimeTick;


	FVector LastLocNetRep;
	FVector LocNetRep;
	FVector VeloNetRep;
	
	FVector LastLocProxy;
	FVector LocProxy;
	FVector VeloProxy;
	FVector LastVeloProxy;
	

};
