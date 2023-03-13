// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerBackendComponent.h"

UMultiplayerBackendComponent::UMultiplayerBackendComponent() 
{	
	localMasterServerPort = "8000";
	localMasterServerIp = "192.168.142.207";
	baseURL = "192.168.142.207:8000";
}

//----------------Local backend--------------------------------------------------------------------------//

void UMultiplayerBackendComponent::CreateGame(FCreateRequest request, FCallbackBinding callbackBinding)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FCreateJoinResponse"))
		return;	
	TMap<FString, FString> headers;
	FString ContentJsonString;
	GetJsonStringFromStruct<FCreateRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/createGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UMultiplayerBackendComponent::OnResponseReceived<FCreateJoinResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UMultiplayerBackendComponent::JoinGame(FJoinRequest request, FCallbackBinding callbackBinding)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FCreateJoinResponse"))
		return;	
	TMap<FString, FString> headers;
	FString ContentJsonString;
	GetJsonStringFromStruct<FJoinRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/joinGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UMultiplayerBackendComponent::OnResponseReceived<FCreateJoinResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UMultiplayerBackendComponent::GetServerIP(FCallbackBinding callbackBinding)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FCreateJoinResponse"))
		return;
	TMap<FString, FString> headers;	
	TSharedRef<IHttpRequest> Request = GetRequest("/serverIp", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UMultiplayerBackendComponent::OnResponseReceived<FCreateJoinResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UMultiplayerBackendComponent::GetServerState(FCallbackBinding callbackBinding)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FServerResponse"))
		return;
	TMap<FString, FString> headers;
	TSharedRef<IHttpRequest> Request = GetRequest("/getServerState", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UMultiplayerBackendComponent::OnResponseReceived<FServerResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UMultiplayerBackendComponent::ServerReady(FBoolRequest request)
{	
	TMap<FString, FString> headers;
	FString ContentJsonString;
	GetJsonStringFromStruct<FBoolRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/serverReady", ContentJsonString, headers);	
	Request->ProcessRequest();
}

void UMultiplayerBackendComponent::StartMultiGame(FBoolRequest request)
{	
	TMap<FString, FString> headers;	
	FString ContentJsonString;
	GetJsonStringFromStruct<FBoolRequest>(request, ContentJsonString);	
	TSharedRef<IHttpRequest> Request = PostRequest("/startMultiGame", ContentJsonString, headers);
	Request->ProcessRequest();
}

void UMultiplayerBackendComponent::ClientLeft(FJoinRequest request)
{
	TMap<FString, FString> headers;	
	FString ContentJsonString;
	GetJsonStringFromStruct<FJoinRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/clientLeft", ContentJsonString, headers);
	Request->ProcessRequest();
}