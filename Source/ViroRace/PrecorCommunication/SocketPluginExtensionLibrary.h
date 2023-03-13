// Copy Right Test

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <WebSocket/Public/WebSocketBase.h>


//--------HTTP & JSON includes--------
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

#include "SocketPluginExtensionLibrary.generated.h"


UENUM(BlueprintType)
enum class EPrecorWorkoutStatus : uint8
{
	InBackground UMETA(DisplayName = "InBackground"),
	Ready UMETA(DisplayName = "Ready"),
	WorkoutStarting UMETA(DisplayName = "WorkoutStarting"),
	WorkoutResuming UMETA(DisplayName = "WorkoutResuming"),
	WorkoutInProgress UMETA(DisplayName = "WorkoutInProgress"),
	WorkoutInactive UMETA(DisplayName = "WorkoutInactive"),
	WorkoutPaused UMETA(DisplayName = "WorkoutPaused"),
	WorkoutFinished UMETA(DisplayName = "WorkoutFinished"),
	Error UMETA(DisplayName = "Error"),
	EmergencyStop UMETA(DisplayName = "EmergencyStop")
};

//--------------------------PRECOR----------------------------------//


USTRUCT(BlueprintType)
struct FPrecorWorkoutState {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPrecorWorkoutStatus precorWorkoutStatus;
};
//"{\"workoutElapseSeconds\":6,\"accumulatedCalories\":3288,\"accumulatedDistance\":0,\"accumulatedDistanceClimbed\":0,\"currentSpeed\":10,\"currentSpeedKph\":16.09,\"currentSpeedRpm\":30,\"currentCadence\":0,\"currentIncline\":1,\"currentHeartRate\":120,\"currentResistance\":1,\"currentLevel\":1}"
USTRUCT(BlueprintType)
struct FWorkoutStream {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int workoutElapseSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int accumulatedCalories;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float accumulatedDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float accumulatedDistanceClimbed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentSpeedKph;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentSpeedRpm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentCadence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentIncline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentHeartRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentResistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentLevel;
};

USTRUCT(BlueprintType)
struct FPrecorWorkoutStatusDate {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int number1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int number2;
};
USTRUCT(BlueprintType)
struct FMessage {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Method;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Data;
};
USTRUCT(BlueprintType)
struct FSetLevelParam {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int level;
};

USTRUCT(BlueprintType)
struct FPrecorWorkoutStatus {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FPrecorWorkoutStatusDate Data;
};


/**
 * 
 */
UCLASS()
class VIRORACE_API USocketPluginExtensionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void SetLevel(UWebSocketBase* socket, int NewLevel);

	UFUNCTION(BlueprintCallable)
	static bool GetWorkoutStreamFromJson(FString jsonString, FWorkoutStream& workoutStream);

	UFUNCTION(BlueprintCallable)
	static int32 GetProcessWorkoutStateChange(FString jsonString, FPrecorWorkoutState & workoutState);

	template <typename StructType>
	static bool GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	static bool GetStructFromJsonString(FString JsonString, StructType& StructOutput);
};