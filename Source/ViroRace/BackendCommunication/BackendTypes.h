// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BackendTypes.generated.h"

UENUM(BlueprintType)
enum class EWorldName : uint8
{
	Other UMETA(DisplayName = "Other"),
	Andromeda UMETA(DisplayName = "Andromeda"),
	Alps UMETA(DisplayName = "Alps"),
	Scandinavia UMETA(DisplayName = "Scandinavia"),
	Austria UMETA(DisplayName = "Austria"),
	Canaries UMETA(DisplayName = "Canaries"),
	Japan  UMETA(DisplayName = "Japan"),
	Canada UMETA(DisplayName = "Canada"),
	LunarBase UMETA(DisplayName = "LunarBase"),
	Greece UMETA(DisplayName = "Greece"),
	CartoonWorld UMETA(DisplayName = "CartoonWorld")
};

UENUM(BlueprintType)
enum class ETrainingPhase : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	WarmUp UMETA(DisplayName = "warm up"),
	Training UMETA(DisplayName = "training"),
	CoolDown UMETA(DisplayName = "cooldown"),
	TestPMax UMETA(DisplayName = "test pmax"),
	TestVo2Max  UMETA(DisplayName = "test pmax")
};

UENUM(BlueprintType)
enum class EGender : uint8
{
	none  UMETA(DisplayName = "none"),
	Male UMETA(DisplayName = "Male"),
	Female	UMETA(DisplayName = "Female"),
	Other	UMETA(DisplayName = "Other")
};

UENUM(BlueprintType)
enum class EPlayingStyle : uint8
{
	Asynchronous UMETA(DisplayName = "Asynchronous"),
	Simultaneous  UMETA(DisplayName = "Simultaneous"),
};


UENUM(BlueprintType)
enum class EBattleType : uint8
{
	none UMETA(DisplayName = "none"),
	All UMETA(DisplayName = "All"),
	Clan  UMETA(DisplayName = "Clan"),
	FriendVsFriend UMETA(DisplayName = "FriendVsFriend"),
	Competition  UMETA(DisplayName = "Competition"),
};

UENUM(BlueprintType)
enum class EBattleInitiatorType : uint8
{
	none UMETA(DisplayName = "none"),
	User UMETA(DisplayName = "User"),
	Contractor  UMETA(DisplayName = "Contractor"),
	System UMETA(DisplayName = "System"),
};



UENUM(BlueprintType)
enum class EAerobicMachines : uint8
{
	none UMETA(DisplayName = "none"),
	UprightBike UMETA (DisplayName = "UprightBike"),
	RecumbentBike UMETA (DisplayName = "RecumbentBike"),
	Stepper UMETA (DisplayName = "Stepper"),
	EllipticalCrossTrainer UMETA (DisplayName = "EllipticalCrossTrainer"),
	Rower UMETA (DisplayName = "Rower")
};

UENUM(BlueprintType)
enum class EMapSetDifficulty : uint8
{
	None UMETA(DisplayName = "None"),
	Easy UMETA(DisplayName = "Easy"),
	Medium UMETA(DisplayName = "Medium"),
	Hard UMETA(DisplayName = "Hard")
};



USTRUCT(BlueprintType)
struct FCollectiblesCollected {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int PortalPositive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int PortalNegative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int Pendulum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int Hammer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int FlaskPositive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int FlaskNegative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		int ChainOrb;

};

//--------------------------ACTIVITIES----------------------------------//
#pragma region

USTRUCT(BlueprintType)
struct FGameData {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		bool isArcadeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game data")
		FString trainingUnitGuid;
};

USTRUCT(BlueprintType)
struct FTrainingData {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training data")
		FString trainingScenarioType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training data")
		FString trainingUnitGuid;
};

USTRUCT(BlueprintType)
struct FFriendsChallengeRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> guids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isHandicapGranted;
};

USTRUCT(BlueprintType)
struct FGhostsChallengeRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> guids;
};

USTRUCT(BlueprintType)
struct FGhostPosition {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int timeInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float z;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float absoluteSplineDistanceInMeters;
};

USTRUCT(BlueprintType)
struct FGhostRow {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int mapCompletionTimeInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isCompleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostPosition> ghostPositions;
};

USTRUCT(BlueprintType)
struct FGhostRowTemp {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int mapCompletionTimeInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isCompleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostPosition> ghostPositions;
};

USTRUCT(BlueprintType)
struct FGhostData {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int itemIntervalInMiliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostRow> ghostRows;
};

USTRUCT(BlueprintType)
struct FGhostDataTemp {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int itemIntervalInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostRowTemp> ghostRows;
};

USTRUCT(BlueprintType)
struct FActivityPayloadItem {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int durationInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float realSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float inGameSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rawSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float realDistancePassed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float inGameDistancePassed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int kcalBurnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int cadence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int heartRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETrainingPhase trainingPhaseType;
};



USTRUCT(BlueprintType)
struct FupcomingAerobicBattleResponseModel {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString battleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int battleMembersCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime startDateUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime lastMomentToStartGameUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lengthInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapsetName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString promoGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapsetGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBattleType battleType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBattleInitiatorType battleInitiator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMapSetDifficulty battleDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<EAerobicMachines> aerobicMachines;
};

USTRUCT(BlueprintType)
struct FGetUpcomingAerobicBattlesResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FupcomingAerobicBattleResponseModel> upcomingAerobicBattles;
};

USTRUCT(BlueprintType)
struct FStartActivityRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString stationSessionGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTrainingData trainingData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameData gameData;
};
USTRUCT(BlueprintType)
struct FStartActivityResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString startDateTime;
};

USTRUCT(BlueprintType)
struct FStartTrainingUnitActivityRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isArcadeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString trainingUnitGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};

USTRUCT(BlueprintType)
struct FGetUpcomingBattlesRequest {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PageNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PageSize;
};

USTRUCT(BlueprintType)
struct FStartFreeRideActivityRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isArcadeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};
USTRUCT(BlueprintType)
struct FStartTestingUnitActivityRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString testingUnitGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};
USTRUCT(BlueprintType)
struct FStartChallengeActivityRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isArcadeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapSetGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FFriendsChallengeRequest friends;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGhostsChallengeRequest ghosts;
};

USTRUCT(BlueprintType)
struct FGameSummary {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float durationInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float averageRealSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float averageInGameSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float averageRawSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float averageHeartRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float realDistancePassed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float inGameDistancePassed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float kcalBurnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> unrankedReasons;
};

USTRUCT(BlueprintType)
struct FEndActivityRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameSummary gameSummary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localEndDateTime;
};

USTRUCT(BlueprintType)
struct FEndActivityResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString startDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString endDateTime;
};

USTRUCT(BlueprintType)
struct FAddGhostPayloadRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGhostDataTemp ghostData;
};

USTRUCT(BlueprintType)
struct FAddGamePayloadRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int itemIntervalInMiliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FActivityPayloadItem> payloadItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCollectiblesCollected collectiblesCollected;
};

USTRUCT(BlueprintType)
struct FStartSessionForGuestResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString stationSessionGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int bookingDurationMiliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isBookingRequired;
};

USTRUCT(BlueprintType)
struct FAuthenticateStationRequest {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString authenticationCode;
};

USTRUCT(BlueprintType)
struct FAuthenticateStationResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString token;
};


#pragma endregion activities endpoints

//--------------------------MAPS----------------------------------//

#pragma region 



USTRUCT(BlueprintType)
struct FMapQuery {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDeleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int completionTimeInMinutes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString photoUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAvailableInFreeRide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAvailableForMapSets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMapSetDifficulty difficulty;
};

USTRUCT(BlueprintType)
struct FGetMapsResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapQuery> maps;
};

USTRUCT(BlueprintType)
struct FMapsResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapQuery> maps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxTimestamp;
};

USTRUCT(BlueprintType)
struct FMapOrder {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int order;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isForward;
};

USTRUCT(BlueprintType)
struct FMapSetQuery {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString displayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int averageCompletionTimeInMinutes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAvailableInBattles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString promoGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMapSetDifficulty difficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int timestamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDeleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapOrder> maps;
};

UENUM(BlueprintType)
enum class EGhostType : uint8
{
	none UMETA(DisplayName = "none"),
	PlayersBest  UMETA(DisplayName = "PlayersBest"),
	PlayersLatest	UMETA(DisplayName = "PlayersLatest"),
	WorldsBest	UMETA(DisplayName = "WorldsBest"),
	FriendsBest  UMETA(DisplayName = "FriendsBest"),
	BetterThanPlayerAverage	UMETA(DisplayName = "BetterThanPlayerAverage"),
	BetterThanPlayersBest	UMETA(DisplayName = "BetterThanPlayersBest"),
	SecondDecile	UMETA(DisplayName = "SecondDecile"),
	FourthDecile 	UMETA(DisplayName = "FourthDecile"),
	EighthDecile 	UMETA(DisplayName = "EighthDecile ")
};

USTRUCT(BlueprintType)
struct FGetMapSetsResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapSetQuery> mapSets;
};

USTRUCT(BlueprintType)
struct FMapSetsResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapSetQuery> mapSets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxTimestamp;
};

USTRUCT(BlueprintType)
struct FGhostItem {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int completionTimeInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGhostType ghostType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isArcade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gamerNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int decile;
};

USTRUCT(BlueprintType)
struct FGetGhostsForMapSetResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostItem> ghosts;
};

USTRUCT(BlueprintType)
struct FGetGhostPayloadResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ghostGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int itemIntervalInMiliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostRow> ghostRows;
};

USTRUCT(BlueprintType)
struct FGetGhostsPayloadsResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGetGhostPayloadResponse> payloads;
};

#pragma endregion maps endpoints

//--------------------------STATIONS----------------------------------//

#pragma region

UENUM(BlueprintType)
enum class EStationType : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	Fitness UMETA(DisplayName = "Fitness"),
	Aerobic UMETA(DisplayName = "Aerobic")
};

UENUM(BlueprintType)
enum class EAerobicEquipmentType : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	UprightBike UMETA(DisplayName = "UprightBike"),
	RecumbentBike UMETA(DisplayName = "RecumbentBike"),
	Stepper UMETA(DisplayName = "Stepper"),
	EllipticalCrossTrainer UMETA(DisplayName = "EllipticalCrossTrainer"),
	Rower UMETA(DisplayName = "Rower")
};

USTRUCT(BlueprintType)
struct FAerobicEquipmentParameters {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lowestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int highestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxWatsPossibleToGenerate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasHeartRateMeasurement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lowerBoundryOfOptimalRevolutionsPerMinuteRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int higherBoundryOfOptimalRevolutionsPerMinuteRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float decreaseLevelTimeFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float increaseLevelTimeFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float resistanceValueOnLowestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float resistanceValueOnHighestLevel;
};

USTRUCT(BlueprintType)
struct FAerobicEquipment {
	GENERATED_BODY()
	//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	FString guid;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	FString consoleIdentifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString machineIdentifier;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicEquipmentType aerobicEquipmentType;
};

UENUM(BlueprintType)
enum class EProcessingUnitType : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	Bridgeless UMETA(DisplayName = "Fitness"),
	WithBridge  UMETA(DisplayName = "Aerobic")
};

USTRUCT(BlueprintType)
struct FProcessingUnit {
	GENERATED_BODY()
		/*	UPROPERTY(EditAnywhere, BlueprintReadWrite)
			FString identifier;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			FString bluetoothServerMacAddress;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			EProcessingUnitType processingUnitType;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localNetworkIp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localNetworkName;
};

USTRUCT(BlueprintType)
struct FTestingUnit {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString trainingScenarioName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int durationInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicEquipmentType aerobicEquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
};

USTRUCT(BlueprintType)
struct FTestingUnitsResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTestingUnit> testingUnits;
};

USTRUCT(BlueprintType)
struct FStationResponseParameters {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lowestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int highestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxWatsPossibleToGenerate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasHeartRateMeasurement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lowerBoundryOfOptimalRevolutionsPerMinuteRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int higherBoundryOfOptimalRevolutionsPerMinuteRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float decreaseLevelTimeFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float increaseLevelTimeFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float resistanceValueOnLowestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float resistanceValueOnHighestLevel;
};


USTRUCT(BlueprintType)
struct FGetStationResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStationType stationType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAerobicEquipment aerobicEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FProcessingUnit processingUnit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTestingUnitsResponse testingUnits;
};

USTRUCT(BlueprintType)
struct FSession {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString sessionGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString endDateTimeInUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
};

UENUM(BlueprintType)
enum class EBodyModel : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	Masculine UMETA(DisplayName = "Masculine"),
	Feminine   UMETA(DisplayName = "Feminine")
};

USTRUCT(BlueprintType)
struct FFitnessHighScore {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int movesCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int movesAccuracy;
};

USTRUCT(BlueprintType)
struct FAerobicHighScoreOnEquipment {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicEquipmentType aerobicEquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float distanceTraveledInKilometers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxSpeedInKilometersPerHour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxPowerInWatts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxHeartRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int averagePaceInSecondsPerKilometer;
};

USTRUCT(BlueprintType)
struct FAerobicHighScore {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dailyDistanceTraveledInKilometers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAerobicHighScoreOnEquipment> aerobicHighScoreOnEquipment;
};

USTRUCT(BlueprintType)
struct FAthleteHighScores {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int dailyKcalBurnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int dailyTrainingTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAerobicHighScore aerobicHighScores;


};

USTRUCT(BlueprintType)
struct FAthleteMeasurments {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float weightInKilograms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int heightInCentimeters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float vo2Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maximalHeartRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int powerForLactateThresholdInWattsOnUprightBike;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int averagePowerForVo2MaxInWattsOnUprightBike;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maximalPowerInWattsOnUprightBike;
};

USTRUCT(BlueprintType)
struct FGamerAvatarQuery {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString renderUrl;
};

USTRUCT(BlueprintType)
struct FGamerEndedGamesStatisticQuery {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int endedRacesCount;
};

USTRUCT(BlueprintType)
struct FGamerCalibrationDataQuery {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int calibrationHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int calibrationHorizontalRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int calibrationVerticalRange;
};

USTRUCT(BlueprintType)
struct FGamerStaticsticsTotalCount {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamesCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamesTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalKcalBurned;
};


USTRUCT(BlueprintType)
struct FGamer {
	GENERATED_BODY()
	/*	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBodyModel bodyModel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString birthDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int age;*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGender gender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString iconGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float energyCoinsAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAthleteHighScores highScores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAthleteMeasurments measurements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGamerEndedGamesStatisticQuery endedGamesStatistics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGamerStaticsticsTotalCount gameStatistics;
};

UENUM(BlueprintType)
enum class ETrainingType : uint8
{
	Ivalid  UMETA(DisplayName = "Invalid data"),
	Aerobic UMETA(DisplayName = "Aerobic"),
	Fitness	UMETA(DisplayName = "Fitness ")
};

USTRUCT(BlueprintType)
struct FNextTrainingUnitContext {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETrainingType trainingType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicEquipmentType aerobicEquipmentType;
};

USTRUCT(BlueprintType)
struct FActiveSession {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSession session;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGamer gamer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FNextTrainingUnitContext trainingUnit;
};

USTRUCT(BlueprintType)
struct FStationContextResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasActiveSession;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FActiveSession activeSession;
};

#pragma endregion stations endpoints

//--------------------------TRAINING PLANS----------------------------------//

#pragma region

UENUM(BlueprintType)
enum class EAerobicMoveType : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	HeartRateAerobicMove UMETA(DisplayName = "HeartRateAerobicMove"),
	PowerAerobicMove  UMETA(DisplayName = "PowerAerobicMove ")
};

USTRUCT(BlueprintType)
struct FAerobicMoveResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicMoveType aerobicMoveType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int durationInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int valueMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int valueMax;
};

USTRUCT(BlueprintType)
struct FAerobicSetResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETrainingPhase trainingPhase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAerobicMoveResponse> aerobicMoves;
};

USTRUCT(BlueprintType)
struct FAerobicTrainingUnitResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicEquipmentType aerobicEquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int powerChangeScenarioPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int heartRateChangeScenarioPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAerobicSetResponse> aerobicSets;
};


UENUM(BlueprintType)
enum class EFitnesssChallenge : uint8
{
	Ivalid UMETA(DisplayName = "Invalid data"),
	Exercising UMETA(DisplayName = "Exercising"),
	Shooting UMETA(DisplayName = "Shooting"),
	Boxing UMETA(DisplayName = "Boxing"),
	Slashing  UMETA(DisplayName = "Slashing ")
};
USTRUCT(BlueprintType)
struct FFitnessMove {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		int repetitionNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		int moveNumber;
};

USTRUCT(BlueprintType)
struct FFitnessExercise {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		EFitnesssChallenge fitnesssChallenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		int durationInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		int beatsPerMinute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		TArray<FFitnessMove> fitnessMoves;
};

USTRUCT(BlueprintType)
struct FFitnessSet {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		ETrainingPhase trainingPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		TArray<FFitnessExercise> fitnessExercises;
};

USTRUCT(BlueprintType)
struct FFitnessUnit {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		TArray<FFitnessSet> fitnessSets;
};

USTRUCT(BlueprintType)
struct FFitnessTraining {

	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		FString trainingGuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training plan")
		TArray<FFitnessSet> fitnessSets;
};

#pragma endregion TrainingPlans endpoints

//--------------------------TRAININGS----------------------------------//

USTRUCT(BlueprintType)
struct FGetTestingUnitScenarioResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAerobicSetResponse> aerobicSets;
};


//--------------------------LEADERBOARD----------------------------------//

USTRUCT(BlueprintType)
struct FLeaderboardItem {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ranking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gamerGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gamerNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int completionTimeInMilliseconds;
};

USTRUCT(BlueprintType)
struct FLeaderboardGamer {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ranking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gamerNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int completionTimeInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int playerBetterThanPercentOfPlayers;
};

USTRUCT(BlueprintType)
struct FRaceLeaderboard {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalCount;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLeaderboardItem> leaderboard;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasGamerEverPlayed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardGamer gamerPosition;
};



//--------------------------USERS----------------------------------//

USTRUCT(BlueprintType)
struct FCalibrateGamerRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int calibrationHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int calibrationVerticalRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int calibrationHorizontalRange;
};

USTRUCT(BlueprintType)
struct FActiveUser {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString userGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString nickname;
};

USTRUCT(BlueprintType)
struct FAerobicGameSummary {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString stationGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString userGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		int score;
};

USTRUCT(BlueprintType)
struct FleaderboardPosition {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		int leaderboardPosition;
};

USTRUCT(BlueprintType)
struct FRemoveUser {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString stationGuid;
};

//----------------Local backend--------------------------------------------------------------------------//

USTRUCT(BlueprintType)
struct FCreateRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TrackIndex;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Map;
};

USTRUCT(BlueprintType)
struct FJoinRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserGuid;
};

USTRUCT(BlueprintType)
struct FCreateJoinResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString IP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Port;
};

USTRUCT(BlueprintType)
struct FServerResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsServerEmpty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsServerReady;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool StartMultiGame;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> UsersGuids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TrackIndex;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Map;
};

USTRUCT(BlueprintType)
struct FBoolRequest {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BoolValue;	
};





//--------------------------------Battle------------
UENUM(BlueprintType)
enum class EPbattleMemberStatus : uint8
{
	none UMETA(DisplayName = "none"),
	Played UMETA(DisplayName = "Played"),
	NotPlayed UMETA(DisplayName = "NotPlayed"),
	Walkover UMETA(DisplayName = "Walkover"),
};

UENUM(BlueprintType)
enum class EUserBattlesFilter : uint8
{
	none UMETA(DisplayName = "none"),
	AllWithoutCanceled UMETA(DisplayName = "AllWithoutCanceled"),
	JoinableAndNotEnded UMETA(DisplayName = "JoinableAndNotEnded"),
	NotJoinableAndNotEnded UMETA(DisplayName = "NotJoinableAndNotEnded"),
	Ended UMETA(DisplayName = "Ended"),
	Canceled UMETA(DisplayName = "Canceled"),
};

UENUM(BlueprintType)
enum class EUserBattleStatus : uint8
{
	none UMETA(DisplayName = "none"),
	Invited UMETA(DisplayName = "Invited"),
	Accepted UMETA(DisplayName = "Accepted"),
	Declined UMETA(DisplayName = "Declined"),
	Walkover UMETA(DisplayName = "Walkover"),
	Outdated  UMETA(DisplayName = "Outdated "),
};


UENUM(BlueprintType)
enum class EModelBattleStatus : uint8
{
	none UMETA(DisplayName = "none"),
	StartPending UMETA(DisplayName = "StartPending"),
	Started UMETA(DisplayName = "Started"),
	Ended UMETA(DisplayName = "Ended"),
	Canceled  UMETA(DisplayName = "Canceled "),
};


UENUM(BlueprintType)
enum class EbattleOpponentType : uint8
{
	none UMETA(DisplayName = "none"),
	Friend UMETA(DisplayName = "Friend"),
	Clan  UMETA(DisplayName = "Clan "),
};


USTRUCT(BlueprintType)
struct FPlayersBestGhostForBattle {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int pageNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int pageSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGhostItem> ghosts;
};


USTRUCT(BlueprintType)
struct FBattleGuid {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString battleGuid;
};

USTRUCT(BlueprintType)
struct FUserDataModel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString iconGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nickname;
};

USTRUCT(BlueprintType)
struct FBattleMemberScoresModel {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FUserDataModel account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPbattleMemberStatus battleMemberStatus;
};

USTRUCT(BlueprintType)
struct FBattlePagingResponseModel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int pageSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int pageNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasNextPage;
};

USTRUCT(BlueprintType)
struct FBattleLeaderboard {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBattleMemberScoresModel> scores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattlePagingResponseModel paging;
};

USTRUCT(BlueprintType)
struct FBattleEnvironmentModel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStationType environmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapsetName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapSetGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapSetDisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lengthInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString promoGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMapSetDifficulty difficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAerobicMachines aerobicMachines;
};

USTRUCT(BlueprintType)
struct FBattleInitiatorModel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBattleInitiatorType battleInitiatorType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString iconGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
};

USTRUCT(BlueprintType)
struct FBattleOpponentModel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EbattleOpponentType battleOpponentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString friendGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString friendNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString friendIconUrl;
};

USTRUCT(BlueprintType)
struct FBattleDetailsData {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString battleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString battleStartDateUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString lastMomentToStartGameUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStationType environmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattleEnvironmentModel battleEnvironment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBattleInitiatorType battleInitiatorType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattleInitiatorModel battleInitiator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattleOpponentModel battleOpponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EModelBattleStatus battleStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBattleType battleType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int takenSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int availableSlots;
};

USTRUCT(BlueprintType)
struct FBattleUserModel {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattleDetailsData battleDetailsData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EUserBattleStatus status;
};


USTRUCT(BlueprintType)
struct FBattleUser {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattlePagingResponseModel paging;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBattleUserModel> battles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
};


USTRUCT(BlueprintType)
struct FStartBattle {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString battleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isArcadeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString mapSetGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};


USTRUCT(BlueprintType)
struct FSetSerwerMultiIP {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString multiplayerServerIpAddress;

};

USTRUCT(BlueprintType)
struct FGetSerwerMultiIP {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isSet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString multiplayerServerIpAddress;
};


USTRUCT(BlueprintType)
struct FFriendItem {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString friendGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString friendNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString friendIconGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isInTheSameClan;
};


USTRUCT(BlueprintType)
struct FFriendList {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FFriendItem> friends;
};

//-------------------------Shop-------------------

UENUM(BlueprintType)
enum class EvehicleType : uint8
{
	none UMETA(DisplayName = "none"),
	HoverBike UMETA(DisplayName = "HoverBike"),
	RealisticBike UMETA(DisplayName = "RealisticBike"),
	HoverCraft UMETA(DisplayName = "HoverCraft"),
	Machine   UMETA(DisplayName = "Machine"),
};


USTRUCT(BlueprintType)
struct FGamerVehiclesItem {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEquipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString displayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString photoUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int priceInEnergyCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isGivenToNewGamers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString vehicleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EvehicleType vehicleType;
};


USTRUCT(BlueprintType)
struct FGamerVehicles {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGamerVehiclesItem> vehicles;
};


USTRUCT(BlueprintType)
struct FShopOwnedVehicles {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEquipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString vehicleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EvehicleType vehicleType;
};

USTRUCT(BlueprintType)
struct FShopVehiclesToBuy {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int priceInEnergyCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString categoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString productGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString vehicleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EvehicleType vehicleType;
};

USTRUCT(BlueprintType)
struct FShopVehiclesImpossibleToBuy {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString vehicleGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EvehicleType vehicleType;
};

USTRUCT(BlueprintType)
struct FShopVehicles {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FShopOwnedVehicles> ownedVehicles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FShopVehiclesToBuy> vehiclesToBuy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FShopVehiclesImpossibleToBuy> vehiclesImpossibleToBuy;
};

USTRUCT(BlueprintType)
struct FVehiclesGuid {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString vehicleGuid;
};

USTRUCT(BlueprintType)
struct FShopOwnedFlares {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEquipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString flareGuid;
};

USTRUCT(BlueprintType)
struct FShopFlaresToBuy {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int priceInEnergyCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString categoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString productGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString flareGuid;
};

USTRUCT(BlueprintType)
struct FFlareGuid {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString flareGuid;
};


USTRUCT(BlueprintType)
struct FShopFlares {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FShopOwnedFlares> ownedFlares;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FShopFlaresToBuy> flaresToBuy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FFlareGuid> flaresImpossibleToBuy;
};

USTRUCT(BlueprintType)
struct FUserEC {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoinsAmount;
};

//--------------------------------------Subscriptions---------------------------

UENUM(BlueprintType)
enum class ESubscriptionMode : uint8
{
	noValid UMETA(DisplayName = "noValid"),
	None UMETA(DisplayName = "None"),
	Home UMETA(DisplayName = "Home"),
	Pro  UMETA(DisplayName = "Pro"),
};

UENUM(BlueprintType)
enum class ERenewalPeriod : uint8
{
	None UMETA(DisplayName = "None"),
	Monthly UMETA(DisplayName = "Monthly"),
	Yearly  UMETA(DisplayName = "Yearly"),
};

USTRUCT(BlueprintType)
struct FUserSubscription {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESubscriptionMode subscriptionMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERenewalPeriod renewalPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localEndDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString subscriptionInstanceGuid;
};

//--------------------------------------Purchases---------------------------

UENUM(BlueprintType)
enum class EOrderStatus : uint8
{
	none UMETA(DisplayName = "none"),
	Draft UMETA(DisplayName = "Draft"),
	Confirmed UMETA(DisplayName = "Confirmed"),
	Paid  UMETA(DisplayName = "Paid"),
	Canceled UMETA(DisplayName = "Canceled"),
	Completed  UMETA(DisplayName = "Completed"),

};

USTRUCT(BlueprintType)
struct FOrderStatusResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EOrderStatus orderStatus;
};


USTRUCT(BlueprintType)
struct FBuyNowWithEC {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString productId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString categoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float price;
};

UENUM(BlueprintType)
enum class EOrderResultStatus : uint8
{
	None UMETA(DisplayName = "None"),
	Ok UMETA(DisplayName = "Ok"),
	ProductPriceChanged  UMETA(DisplayName = "ProductPriceChanged"),
	ProductNotAvailable UMETA(DisplayName = "ProductNotAvailable"),
	PurchaseLimitReached  UMETA(DisplayName = "PurchaseLimitReached"),
	TransactionFailed UMETA(DisplayName = "TransactionFailed"),
	InsufficientFunds  UMETA(DisplayName = "InsufficientFunds"),
	OrderCanceled UMETA(DisplayName = "OrderCanceled"),
	RequiresAction   UMETA(DisplayName = "RequiresAction "),
};


USTRUCT(BlueprintType)
struct FBuyNowWithECResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EOrderResultStatus orderResultStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString orderGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int orderId;
};

UENUM(BlueprintType)
enum class ELevelFitness : uint8
{
	None UMETA(DisplayName = "None"),
	MotivatedPotato UMETA(DisplayName = "MotivatedPotato"),
	FitNormal  UMETA(DisplayName = "FitNormal"),
	BeginningSportsman UMETA(DisplayName = "BeginningSportsman"),
	SkillfulMuscleman  UMETA(DisplayName = "SkillfulMuscleman"),
	ProfessionalAthlete  UMETA(DisplayName = "ProfessionalAthlete"),
};


USTRUCT(BlueprintType)
struct FUserProfileLevel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalKcal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int nextLevelKcalProgress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int nextLevelKcalRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELevelFitness nextLevelFitnessRequirement;
};



USTRUCT(BlueprintType)
struct FUserProfileAvatar {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELevelFitness upperBodyFitnessLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELevelFitness lowerBodyFitnessLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELevelFitness maxFitnessLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString avatarGraphicUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString avatarTemplateGuid;
};

USTRUCT(BlueprintType)
struct FGamerSettings {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FString, FString> gamerSettings;
};
