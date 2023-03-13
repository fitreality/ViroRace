// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DownloadImageBackend.generated.h"

class UTexture2DDynamic;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadImageDelegateApi, UTexture2DDynamic*, Texture);

/**
 * 
 */
UCLASS()
class VIRORACE_API UDownloadImageBackend : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UDownloadImageBackend* DownloadImage(FString URL, FString ApiKey);

	UPROPERTY(BlueprintAssignable)
		FDownloadImageDelegateApi OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FDownloadImageDelegateApi OnFail;

	void Start(FString URL, FString ApiKey);

private:

	/** Handles image requests coming from the web */
	void HandleImageRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
