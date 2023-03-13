// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BackendCommunication/WebCommunicationBaseComponent.h"
#include "BackendCommunication/BackendTypes.h"
#include "MultiplayerBackendComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), config = Game)
class VIRORACE_API UMultiplayerBackendComponent : public UWebCommunicationBaseComponent
{
	GENERATED_BODY()


	
public:
	//----------------Local backend--------------------------------------------------------------------------//
	UMultiplayerBackendComponent();
//Response type: FCreateJoinResponse
	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void CreateGame(FCreateRequest request, FCallbackBinding callbackBinding);

	//Response type: FCreateJoinResponse
	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void JoinGame(FJoinRequest request, FCallbackBinding callbackBinding);

	//Response type: FServerResponse
	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void GetServerState(FCallbackBinding callbackBinding);	
	
	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void GetServerIP(FCallbackBinding callbackBinding);	
	
	//There's no response
	
	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void ServerReady(FBoolRequest request);

	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void StartMultiGame(FBoolRequest request);

	UFUNCTION(BlueprintCallable, Category = "Local backend")
		void ClientLeft(FJoinRequest request);

protected:
	UPROPERTY(Config, BlueprintReadOnly)
	FString localMasterServerIp;
	UPROPERTY(Config, BlueprintReadOnly)
	FString localMasterServerPort;
	UPROPERTY(Config, BlueprintReadOnly)
	TArray<FString> UsersData;
};
