// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOneLevelData.generated.h"

/**
 * 
 */

class APGPortal;
class 	ULevelStreamingDynamic;

UCLASS()
class VIRORACE_API AGameOneLevelData : public AActor
{
	GENERATED_BODY()
	
public:
	AGameOneLevelData(const FObjectInitializer& InOI);
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GatherPortals(const TArray<ULevelStreamingDynamic*>& Levels);

	UFUNCTION(BlueprintCallable)
	void RegisterPortals(const TArray<APGPortal*>& InStartPortals, const TArray<APGPortal*>& InEndPortals);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetPortals(TArray<APGPortal*>& OutStartPortals, TArray<APGPortal*>& OutEndPortals);

protected:
	UPROPERTY()
	TArray<APGPortal*> StartPortals;

	UPROPERTY()
	TArray<APGPortal*> EndPortals;
};
