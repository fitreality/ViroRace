// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerfectGymTypes.h"
#include "PGPortal.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPortalEnteredDelegate, class APGPortal*, Portal, class APawn*, Pawn);

UCLASS()
class VIRORACE_API APGPortal : public AActor
{
	GENERATED_BODY()
	
public:
	APGPortal(const FObjectInitializer& InOI);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	EPortalType PortalType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	FPortalConfig PortalConfig;

	UPROPERTY(BlueprintAssignable, Category = "Portal")
	FOnPortalEnteredDelegate OnPortalEntered;

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void EnterPortal(APGPortal* Portal, APawn* Pawn);

protected:

	
};
