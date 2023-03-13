// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "BackendTypes.h"
#include "WebCommunicationBaseComponent.h"
#include "BackendCommunicationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResponseReceived, int, responseCode, FString, message);

DECLARE_LOG_CATEGORY_EXTERN(ViroBackendCommunication, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIRORACE_API UBackendCommunicationComponent : public UWebCommunicationBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackendCommunicationComponent();


	//-----------------Subscriptions---------------------------------------------------------------------------------//


	UFUNCTION(BlueprintCallable, Category = "Subscriptions")
		void GetUserSubscription(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);
	//-----------------Purchases---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Purchases")
		void GetEnergyCoins(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Purchases")
		void GetOrderStatus(FCallbackBinding callbackBinding, FString request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Purchases")
		void BuyNowWithEnergyCoins(FCallbackBinding callbackBinding, FBuyNowWithEC request, const TMap<FString, FString> &headers);

	//-----------------Gamer---------------------------------------------------------------------------------//
	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetGamerData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetUserProfileLevel(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetUserAvatarData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetGamerVehicles(FCallbackBinding callbackBinding, bool Equipped, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetGamerVehiclesShop(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void EquipVehicle(FCallbackBinding callbackBinding, FVehiclesGuid request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetGamerFlares(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void EquipFlare(FCallbackBinding callbackBinding, FFlareGuid request,  const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void GetGamerSettings(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamer")
		void UpdateGamerSettings(FCallbackBinding callbackBinding, FGamerSettings request, const TMap<FString, FString> &headers);


	//-----------------Batttle---------------------------------------------------------------------------------//
	UFUNCTION(BlueprintCallable, Category = "Friends")
	void GetFriends(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//-----------------Batttle---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Battles endpoints")
	void GetPlayersBestGhostForBattle(FCallbackBinding callbackBinding, FString BattleGuid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Battles endpoints")
	void GetUsersBattles(FCallbackBinding callbackBinding, EBattleType BattleType,  EUserBattlesFilter UserBattlesFilter, int32 PageNumber, int32 PageSize,  const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Battles endpoints")
	void DeclineBattleInvitation(FCallbackBinding callbackBinding, FBattleGuid request,  const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Battles endpoints")
	void JoinBattle(FCallbackBinding callbackBinding, FBattleGuid request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Battles endpoints")
	void GetBattleLeaderboard(FCallbackBinding callbackBinding, FString BattleGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Battles endpoints")
	void StartBattleGame(FCallbackBinding callbackBinding, FStartBattle request, const TMap<FString, FString> &headers);

	//-----------------Multi---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
		void SetStationsLocationMultiplayerServerIpAddress(FCallbackBinding callbackBinding, FSetSerwerMultiIP request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
		void GetStationsLocationMultiplayerServerIpAddress(FCallbackBinding callbackBinding,  const TMap<FString, FString> &headers);


	//-----------------ACTIVITES---------------------------------------------------------------------------------//

	//Response type: StartActivityResponse
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
	void StartTrainingUnitGame(FCallbackBinding callbackBinding, FStartTrainingUnitActivityRequest request, const TMap<FString, FString> &headers);
	

	//Response type: GetUpcomingAerobBattlesResponse
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
		void GetUpcomingBattles(FCallbackBinding callbackBinding, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	//Response type: StartActivityResponse
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
	void StartFreeRideGame(FCallbackBinding callbackBinding, FStartFreeRideActivityRequest request, const TMap<FString, FString> &headers);

	//Response type: StartActivityResponse
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
	void StartTestingUnitGame(FCallbackBinding callbackBinding, FStartTestingUnitActivityRequest request, const TMap<FString, FString> &headers);

	//Response type: StartActivityResponse
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
	void StartRaceGame(FCallbackBinding callbackBinding, FStartChallengeActivityRequest request, const TMap<FString, FString> &headers);

	//Response type: EndActivityResponse
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
	void EndGame(FCallbackBinding callbackBinding, FEndActivityRequest endActivityRequest, const TMap<FString, FString> &headers);

	//Response type: payloadRequest
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
		void AddGhostPayload(FCallbackBinding callbackBinding, FAddGhostPayloadRequest payloadRequest, const TMap<FString, FString> &headers);

	//Response type: payloadRequest
	UFUNCTION(BlueprintCallable, Category = "Activities endpoints")
		void AddGamePayload(FCallbackBinding callbackBinding, FAddGamePayloadRequest payloadRequest, const TMap<FString, FString> &headers);

	//-----------------Leaderboard---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetRaceLeaderboard(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, int32 PageNumber, int32 PageSize, const TMap<FString, FString>& headers);

	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetRaceLocalLeaderboard(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, int32 PageNumber, int32 PageSize, const TMap<FString, FString>& headers);


	//-----------------MAPS---------------------------------------------------------------------------------//

	//Response type: GetMapsResponse
	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetMaps(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetMapsByTimestamp(FCallbackBinding callbackBinding, int Timestamp, int PageSize, const TMap<FString, FString> &headers);

	//Response type: GetMapSetsResponse
	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetMapSets(FCallbackBinding callbackBinding, bool activeOnly, const TMap<FString, FString> &headers);

	//Response type: GetMapSetsResponse
	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
		void GetMapSetsByTimestamp(FCallbackBinding callbackBinding, int Timestamp, int PageSize, const TMap<FString, FString> &headers);

	//Response type: GetGhostsForMapSetResponse
	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetGhostsForMapSet(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, const TMap<FString, FString> &headers);

	//Response type: GetGhostsForMapSetResponse
	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetGhostsSetForMapSet(FCallbackBinding callbackBinding, FString mapSetGuid, bool isArcade, const TMap<FString, FString>& headers);

	//Response type: GetGhostsPayloadsResponse
	UFUNCTION(BlueprintCallable, Category = "Maps endpoints")
	void GetGhostsPayloads(FCallbackBinding callbackBinding, TArray<FString> ghostGuids, const TMap<FString, FString> &headers);

	//-----------------STATIONS---------------------------------------------------------------------------------//

	//Response type: GetStationResponse
	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
	void GetStation(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//Response type: StationContextResponse
	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
	void GetStationContext(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
		void AuthenticateStation(FCallbackBinding callbackBinding, FAuthenticateStationRequest request,const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
	void StartSessionForGuest(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Stations endpoints")
	void EndSession(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//-----------------TRAINING PLANS---------------------------------------------------------------------------------//

	//Response type: AerobicTrainingUnitResponse
	UFUNCTION(BlueprintCallable, Category = "training plans endpoints")
	void GetNextAerobicTrainingUnit(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//Response type: FitnessTraining
	UFUNCTION(BlueprintCallable, Category = "training plans endpoints")
	void GetNextFintessTrainingUnit(FCallbackBinding callbackBinding, FString stationGuid, const TMap<FString, FString> &headers);

	//-----------------TRAININGS---------------------------------------------------------------------------------//
	
	//Response type: TestingUnitsResponse
	UFUNCTION(BlueprintCallable, Category = "training endpoints")
	void GetTestingUnitsForStation(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//Response type: GetTestingUnitScenarioResponse
	UFUNCTION(BlueprintCallable, Category = "training endpoints")
	void GetTestingUnitScenario(FCallbackBinding callbackBinding, FString testingUnitGuid, const TMap<FString, FString> &headers);

	//-----------------IHRSA---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "IHRSA endpoints")
	void GetActiveUser(FCallbackBinding callbackBinding, FString stationGuid, const TMap<FString, FString> &headers);

	//Response type: leaderboardPosition
	UFUNCTION(BlueprintCallable, Category = "IHRSA endpoints")
	void AerobicGameSummary(FCallbackBinding callbackBinding, FAerobicGameSummary request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "IHRSA endpoints")
		void RemoveActiveUser(FRemoveUser stationGuid, const TMap<FString, FString> &headers);

	
	//-----------------USERS---------------------------------------------------------------------------------//

	//there's no response
	UFUNCTION(BlueprintCallable, Category = "users")
	void CalibrateUser(FCallbackBinding callbackBinding, FCalibrateGamerRequest request, const TMap<FString, FString> &headers);


	UFUNCTION(BlueprintCallable, Category = "Log")
	void WriteToLog(FString callbackName, FString ContentJsonString);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
