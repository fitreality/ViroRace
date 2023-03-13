// Fill out your copyright notice in the Description page of Project Settings.

#include "BackendCommunicationComponent.h"

//--------HTTP & JSON includes--------
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "ConfigFileLoad.h"


DEFINE_LOG_CATEGORY(ViroBackendCommunication);

// Sets default values for this component's properties
UBackendCommunicationComponent::UBackendCommunicationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UBackendCommunicationComponent::BeginPlay()
{
	Super::BeginPlay();
	bool Exist;
	FString Environment;
	UConfigFileLoad::LoadStringFromConfigFile("Environment", Environment, Exist);
	if (Exist)
	{
		if (Environment == "Testing")
		{
			baseURL = "https://aerobicgame-api-testing.viro.fit/api/";
			UE_LOG(ViroBackendCommunication, Log, TEXT("Environment: Testing | URL: %s"), *baseURL);
		}
		else if (Environment == "Prod")
		{
			baseURL = "https://aerobicgame-api-prod.viro.fit/api/";
			UE_LOG(ViroBackendCommunication, Log, TEXT("Environment: Prod | URL: %s"), *baseURL);
		}
		else
		{
			Exist = false;
		}
		if (!Exist) {
			baseURL = "https://aerobicgame-api-testing.viro.fit/api/";
			UE_LOG(ViroBackendCommunication, Log, TEXT("Environment URL Not Found. | Environment: %s | Loaded default URL: %s"), *Environment, *baseURL);
		}
		UWebCommunicationBaseComponent::baseURL = baseURL;
	}
	else {
		baseURL = "https://aerobicgame-api-prod.viro.fit/api/";
		UE_LOG(ViroBackendCommunication, Log, TEXT("Environment Not Found"));
	}
	// ...

}


// Called every frame
void UBackendCommunicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBackendCommunicationComponent::WriteToLog(FString callbackName, FString ContentJsonString)
{
	UE_LOG(ViroBackendCommunication, Log, TEXT("Endpoint: %s | Request: %s"), *callbackName, *ContentJsonString);
}




//-----------------Subscriptions---------------------------------------------------------------------------------//


void UBackendCommunicationComponent::GetUserSubscription(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FUserSubscription"))
		return;
	FString body = "Subscriptions/GetUserSubscription";
	WriteToLog("GetUserSubscription at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FUserSubscription>, callbackBinding);
	Request->ProcessRequest();
}


//-----------------Purchases---------------------------------------------------------------------------------//




void UBackendCommunicationComponent::GetOrderStatus(FCallbackBinding callbackBinding, FString request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FOrderStatusResponse"))
		return;
	FString body = "Purchases/GetOrderStatus?Guid=" + request;
	WriteToLog("GetOrderStatus at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FOrderStatusResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::BuyNowWithEnergyCoins(FCallbackBinding callbackBinding, FBuyNowWithEC request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBuyNowWithECResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FBuyNowWithEC>(request, ContentJsonString);
	WriteToLog("BuyNowWithEnergyCoins at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Purchases/BuyNowWithEnergyCoins", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBuyNowWithECResponse>, callbackBinding);
	Request->ProcessRequest();
}




void UBackendCommunicationComponent::GetEnergyCoins(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FUserEC"))
		return;
	FString body = "Purchases/GetEnergyCoins";
	WriteToLog("GetEnergyCoins at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FUserEC>, callbackBinding);
	Request->ProcessRequest();
}





//-----------------Gamer---------------------------------------------------------------------------------//


void UBackendCommunicationComponent::GetGamerData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGamer"))
		return;
	FString body = "Gamers/GetGamerData";
	WriteToLog("GetGamerData at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGamer>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetUserProfileLevel(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FUserProfileLevel"))
		return;
	FString body = "Gamers/GetUserProfileLevel";
	WriteToLog("GetUserProfileLevel at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FUserProfileLevel>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetUserAvatarData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FUserProfileAvatar"))
		return;
	FString body = "Gamers/GetUserAvatarData";
	WriteToLog("GetUserAvatarData at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FUserProfileAvatar>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGamerVehicles(FCallbackBinding callbackBinding, bool Equipped, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGamerVehicles"))
		return;
	FString activeOnlyString = Equipped ? "true" : "false";
	FString body = "Gamers/GetGamerVehicles?Equipped=" + activeOnlyString;
	WriteToLog("GetGamerVehicles at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGamerVehicles>, callbackBinding);
	Request->ProcessRequest();
}



void UBackendCommunicationComponent::GetGamerVehiclesShop(FCallbackBinding callbackBinding,  const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FShopVehicles"))
		return;
	FString body = "Gamers/GetGamerVehiclesShop";
	WriteToLog("GetGamerVehiclesShop at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FShopVehicles>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::EquipVehicle(FCallbackBinding callbackBinding, FVehiclesGuid request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FVehiclesGuid>(request, ContentJsonString);
	WriteToLog("EquipVehicle at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Gamers/EquipVehicle", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetGamerFlares(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FShopFlares"))
		return;
	FString body = "Gamers/GetGamerFlares";
	WriteToLog("GetGamerFlares at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FShopFlares>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::EquipFlare(FCallbackBinding callbackBinding, FFlareGuid request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FFlareGuid>(request, ContentJsonString);
	WriteToLog("EquipFlare at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Gamers/EquipFlare", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetGamerSettings(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGamerSettings"))
		return;
	FString body = "Gamers/GetGamerSettings";
	WriteToLog("GetGamerSettings at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGamerSettings>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::UpdateGamerSettings(FCallbackBinding callbackBinding, FGamerSettings request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FGamerSettings>(request, ContentJsonString);
	WriteToLog("UpdateGamerSettings at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Gamers/UpdateGamerSettings", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}




//-----------------Friends---------------------------------------------------------------------------------//
void UBackendCommunicationComponent::GetFriends(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FFriendList"))
		return;
	FString body = "Friends/GetFriends";
	WriteToLog("GetFriends at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FFriendList>, callbackBinding);
	Request->ProcessRequest();
}


//-----------------Multi---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::SetStationsLocationMultiplayerServerIpAddress(FCallbackBinding callbackBinding, FSetSerwerMultiIP request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FSetSerwerMultiIP>(request, ContentJsonString);
	WriteToLog("SetStationsLocationMultiplayerServerIpAddress at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Stations/SetStationsLocationMultiplayerServerIpAddress", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetStationsLocationMultiplayerServerIpAddress(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetSerwerMultiIP"))
		return;
	FString body = "Stations/GetStationsLocationMultiplayerServerIpAddress";
	WriteToLog("GetStationsLocationMultiplayerServerIpAddress at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetSerwerMultiIP>, callbackBinding);
	Request->ProcessRequest();
}



//-----------------Batttle---------------------------------------------------------------------------------//


void UBackendCommunicationComponent::GetPlayersBestGhostForBattle(FCallbackBinding callbackBinding, FString BattleGuid, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FPlayersBestGhostForBattle"))
		return;
	FString body = "Competitions/GetPlayersBestGhostForBattle?BattleGuid=" + BattleGuid;
	WriteToLog("GetPlayersBestGhostForBattle at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FPlayersBestGhostForBattle>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetUsersBattles(FCallbackBinding callbackBinding, EBattleType BattleType, EUserBattlesFilter UserBattlesFilter, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBattleUser"))
		return;

	FString SBattleType;
	switch (BattleType) {
	case EBattleType::none: SBattleType = "FriendVsFriend";
		break;
	case EBattleType::All: SBattleType = "All";
		break;
	case EBattleType::Clan: SBattleType = "Clan";
		break;
	case EBattleType::FriendVsFriend: SBattleType = "FriendVsFriend";
		break;
	case EBattleType::Competition: SBattleType = "Competition";
		break;
	}
	FString SUserBattlesFilter;
	switch (UserBattlesFilter) {
	case EUserBattlesFilter::AllWithoutCanceled: SUserBattlesFilter = "AllWithoutCanceled";
		break;
	case EUserBattlesFilter::JoinableAndNotEnded: SUserBattlesFilter = "JoinableAndNotEnded";
		break;
	case EUserBattlesFilter::NotJoinableAndNotEnded: SUserBattlesFilter = "NotJoinableAndNotEnded";
		break;
	case EUserBattlesFilter::Ended: SUserBattlesFilter = "Ended";
		break;
	case EUserBattlesFilter::Canceled: SUserBattlesFilter = "Canceled";
		break;
	}
	FString body = "Competitions/GetUsersBattles?BattleType=" + SBattleType + "&UserBattlesFilter=" + SUserBattlesFilter + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	WriteToLog("GetUsersBattles at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBattleUser>, callbackBinding);
	Request->ProcessRequest();
}



void UBackendCommunicationComponent::DeclineBattleInvitation(FCallbackBinding callbackBinding, FBattleGuid request,  const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FBattleGuid>(request, ContentJsonString);
	WriteToLog("JoinBattle at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Competitions/DeclineBattleInvitation", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::JoinBattle(FCallbackBinding callbackBinding, FBattleGuid request,  const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FBattleGuid>(request, ContentJsonString);
	WriteToLog("JoinBattle at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Competitions/JoinBattle", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetBattleLeaderboard(FCallbackBinding callbackBinding, FString BattleGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBattleLeaderboard"))
		return;
	FString body = "Competitions/GetBattleLeaderboard?BattleGuid=" + BattleGuid + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	WriteToLog("GetBattleLeaderboard at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBattleLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::StartBattleGame(FCallbackBinding callbackBinding, FStartBattle request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStartActivityResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FStartBattle>(request, ContentJsonString);
	WriteToLog("StartBattleGame at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartBattleGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStartActivityResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::StartTrainingUnitGame(FCallbackBinding callbackBinding, FStartTrainingUnitActivityRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStartActivityResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FStartTrainingUnitActivityRequest>(request, ContentJsonString);
	WriteToLog("StartTrainingUnitGame at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartTrainingUnitGame", ContentJsonString,headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStartActivityResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetUpcomingBattles(FCallbackBinding callbackBinding, int32 PageNumber, int32 PageSize, const TMap<FString, FString>& headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetUpcomingAerobicBattlesResponse"))
		return;
	FString body = "Competitions/GetUpcomingBattles?PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	WriteToLog("GetUpcomingBattles at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetUpcomingAerobicBattlesResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::StartFreeRideGame(FCallbackBinding callbackBinding, FStartFreeRideActivityRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStartActivityResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FStartFreeRideActivityRequest>(request, ContentJsonString);
	WriteToLog("StartFreeRideGame at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartFreeRideGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStartActivityResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::StartTestingUnitGame(FCallbackBinding callbackBinding, FStartTestingUnitActivityRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStartActivityResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FStartTestingUnitActivityRequest>(request, ContentJsonString);
	WriteToLog("StartTestingUnitGame at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartTestingUnitGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStartActivityResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::StartRaceGame(FCallbackBinding callbackBinding, FStartChallengeActivityRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStartActivityResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FStartChallengeActivityRequest>(request, ContentJsonString);
	WriteToLog("StartRaceGame at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartRaceGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStartActivityResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::EndGame(FCallbackBinding callbackBinding, FEndActivityRequest endActivityRequest, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FEndActivityResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FEndActivityRequest>(endActivityRequest, ContentJsonString);
	WriteToLog("EndGame at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/EndGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FEndActivityResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::AddGhostPayload(FCallbackBinding callbackBinding, FAddGhostPayloadRequest payloadRequest, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FAddGhostPayloadRequest>(payloadRequest, ContentJsonString);
	WriteToLog("AddGhostPayload at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/AddGhostPayload", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::AddGamePayload(FCallbackBinding callbackBinding, FAddGamePayloadRequest payloadRequest, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FAddGamePayloadRequest>(payloadRequest, ContentJsonString);
	WriteToLog("AddGamePayload at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/AddGamePayload", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}







//-----------------Leaderboard---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetRaceLeaderboard(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, int32 PageNumber, int32 PageSize, const TMap<FString, FString>& headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FRaceLeaderboard"))
		return;
	FString activeOnlyString = isArcade ? "true" : "false";
	FString body = "Leaderboards/GetRaceLeaderboard?MapSetGuid=" + mapSetGuid + "&IsArcadeMode=" + activeOnlyString + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	WriteToLog("GetRaceLeaderboard at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FRaceLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetRaceLocalLeaderboard(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, int32 PageNumber, int32 PageSize, const TMap<FString, FString>& headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FRaceLeaderboard"))
		return;
	FString activeOnlyString = isArcade ? "true" : "false";
	FString body = "Leaderboards/GetRaceLocalLeaderboard?MapSetGuid=" + mapSetGuid + "&IsArcadeMode=" + activeOnlyString + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	WriteToLog("GetRaceLeaderboard at " + headers.FindRef(FString("Authorization")), body);
	TSharedRef<IHttpRequest> Request = GetRequest(body, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FRaceLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}

//-----------------MAPS---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetMaps(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{	
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetMapsResponse"))
		return;
	WriteToLog("GetMaps at " + headers.FindRef(FString("Authorization")),"");
	TSharedRef<IHttpRequest> Request = GetRequest("Maps/GetMaps", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetMapsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetMapsByTimestamp(FCallbackBinding callbackBinding, int Timestamp, int PageSize, const TMap<FString, FString> &headers)
{
	FString content = "Maps/GetMapsByTimestamp";
	content += "?Timestamp=" + FString::FromInt(Timestamp) + "&PageSize=" + FString::FromInt(PageSize);

	if (!CheckIfCallbackIsCorrect(callbackBinding, "FMapsResponse"))
		return;
	WriteToLog("GetMapsByTimestamp at " + headers.FindRef(FString("Authorization")), content);
	TSharedRef<IHttpRequest> Request = GetRequest(content, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FMapsResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetMapSets(FCallbackBinding callbackBinding, bool activeOnly, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetMapSetsResponse"))
		return;
	FString activeOnlyString =  activeOnly ? "true" : "false";
	WriteToLog("GetMapSets at " + headers.FindRef(FString("Authorization")), activeOnlyString);
	TSharedRef<IHttpRequest> Request = GetRequest("Maps/GetMapSets?ActiveOnly=" + activeOnlyString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetMapSetsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetMapSetsByTimestamp(FCallbackBinding callbackBinding, int Timestamp, int PageSize, const TMap<FString, FString> &headers)
{
	FString content = "Maps/GetMapSetsByTimestamp";
	content += "?Timestamp=" + FString::FromInt(Timestamp) + "&PageSize=" + FString::FromInt(PageSize);
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FMapSetsResponse"))
		return;
	WriteToLog("GetMapSetsByTimestamp at " + headers.FindRef(FString("Authorization")), content);
	TSharedRef<IHttpRequest> Request = GetRequest(content, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FMapSetsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGhostsForMapSet(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetGhostsForMapSetResponse"))
		return;
	FString content = "Maps/GetGhostsForMapSet";
	FString isArcadeString = isArcade ? "true" : "false";
	content += "?MapSetGuid=" + mapSetGuid + "&IsArcade=" + isArcadeString;
	WriteToLog("GetGhostsForMapSet at " + headers.FindRef(FString("Authorization")), content);
	TSharedRef<IHttpRequest> Request = GetRequest(content, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetGhostsForMapSetResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGhostsSetForMapSet(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, const TMap<FString, FString>& headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetGhostsForMapSetResponse"))
		return;

	FString content = "Maps/GetGhostsSetForMapSet";
	FString isArcadeString = isArcade ? "true" : "false";
	content += "?MapSetGuid=" + mapSetGuid + "&IsArcade=" + isArcadeString;
	WriteToLog("GetGhostsSetForMapSet at " + headers.FindRef(FString("Authorization")), content);
	TSharedRef<IHttpRequest> Request = GetRequest(content, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetGhostsForMapSetResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetGhostsPayloads(FCallbackBinding callbackBinding, TArray<FString> ghostGuids, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetGhostsPayloadsResponse"))
		return;
	FString content = "Maps/GetGhostsPayloads?";
	for (int i = 0; i < ghostGuids.Num(); i++)
	{
		content += "GhostGuids=" + ghostGuids[i];
		if (i != ghostGuids.Num() - 1) content += "&";
	}
	WriteToLog(callbackBinding.callbackName, content);
	TSharedRef<IHttpRequest> Request = GetRequest(content, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetGhostsPayloadsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetStation(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetStationResponse"))
		return;
	WriteToLog("GetStation at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = GetRequest("Stations/GetStation", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGetStationResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetStationContext(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStationContextResponse"))
		return;
	WriteToLog("GetStationContext at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = GetRequest("Stations/GetStationContext", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStationContextResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::AuthenticateStation(FCallbackBinding callbackBinding, FAuthenticateStationRequest request,const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FAuthenticateStationResponse"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FAuthenticateStationRequest>(request, ContentJsonString);
	WriteToLog( "AuthenticateStation at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Stations/AuthenticateStation", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FAuthenticateStationResponse>, callbackBinding);
	Request->ProcessRequest();
}
void UBackendCommunicationComponent::StartSessionForGuest(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FStartSessionForGuestResponse"))
		return;
	WriteToLog("StartSessionForGuest at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = PostRequestNoJson("Stations/StartSessionForGuest", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FStartSessionForGuestResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::EndSession(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	WriteToLog("EndSession at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = PostRequestNoJson("Stations/EndStationSession", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetNextAerobicTrainingUnit(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FAerobicTrainingUnitResponse"))
		return;
	WriteToLog("GetNextAerobicTrainingUnit at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = GetRequest("TrainingPlans/GetNextAerobicTrainingUnit", headers);
	Request->OnProcessRequestComplete().BindUObject(this, 
		&UBackendCommunicationComponent::OnResponseReceived<FAerobicTrainingUnitResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetNextFintessTrainingUnit(FCallbackBinding callbackBinding, FString stationGuid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FFitnessTraining"))
		return;
	WriteToLog("GetNextFintessTrainingUnit at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = GetRequest("TrainingPlans/GetNextFitnessTrainingUnit?StationGuid=" + stationGuid, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FFitnessTraining>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetTestingUnitsForStation(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FTestingUnitsResponse"))
		return;
	WriteToLog("GetTestingUnitsForStation at " + headers.FindRef(FString("Authorization")), "");
	TSharedRef<IHttpRequest> Request = GetRequest("Trainings/GetTestingUnitsForStation", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FTestingUnitsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetTestingUnitScenario(FCallbackBinding callbackBinding, FString testingUnitGuid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetTestingUnitScenarioResponse"))
		return;
	FString content = "Trainings/GetTestingUnitScenario?TestingUnitGuid=" + testingUnitGuid;
	content += "&TestingUnitGuid=" + testingUnitGuid;
	WriteToLog("GetTestingUnitScenario at " + headers.FindRef(FString("Authorization")), content);
	TSharedRef<IHttpRequest> Request = GetRequest(content, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FTestingUnitsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::CalibrateUser(FCallbackBinding callbackBinding, FCalibrateGamerRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "void"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FCalibrateGamerRequest>(request, ContentJsonString);
	WriteToLog("CalibrateUser at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Users/CalibrateUser", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}



void UBackendCommunicationComponent::GetActiveUser(FCallbackBinding callbackBinding, FString stationGuid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FActiveUser"))
		return;
	WriteToLog("GetActiveUser at " + headers.FindRef(FString("Authorization")), stationGuid);
	TSharedRef<IHttpRequest> Request = GetRequest("GameManagement/GetActiveUser?StationGuid=" + stationGuid, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FActiveUser>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::AerobicGameSummary(FCallbackBinding callbackBinding, FAerobicGameSummary request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FleaderboardPosition"))
		return;
	FString ContentJsonString;
	GetJsonStringFromStruct<FAerobicGameSummary>(request, ContentJsonString);
	WriteToLog("AerobicGameSummary at " + headers.FindRef(FString("Authorization")), ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("GameManagement/FitnessGameSummary", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FleaderboardPosition>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::RemoveActiveUser(FRemoveUser request, const TMap<FString, FString> &headers)
{
	FString ContentJsonString;
	GetJsonStringFromStruct<FRemoveUser>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("GameManagement/RemoveActiveUser", ContentJsonString, headers);
	Request->OnProcessRequestComplete();
	Request->ProcessRequest();
}
