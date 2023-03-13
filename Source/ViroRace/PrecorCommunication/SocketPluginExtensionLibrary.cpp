// Copy Right Test

#include "SocketPluginExtensionLibrary.h"

void USocketPluginExtensionLibrary::SetLevel(UWebSocketBase * socket, int NewLevel)
{
	if (!socket) return;

	FSetLevelParam param;
	param.level = NewLevel;

	FString jsonString;

	GetJsonStringFromStruct<FSetLevelParam>(param, jsonString);

	FMessage msg;
	msg.Method = "SetLevel";
	msg.Data = jsonString;

	FString sendMsg;
	GetJsonStringFromStruct<FMessage>(msg, sendMsg);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *sendMsg);
	socket->SendText(sendMsg);
}

bool USocketPluginExtensionLibrary::GetWorkoutStreamFromJson(FString jsonString, FWorkoutStream & workoutStream)
{	
	FMessage msg;
	if (!GetStructFromJsonString<FMessage>(jsonString, msg))
		return false;
	jsonString = msg.Data;
	UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *msg.Method, *msg.Data);
	if(msg.Method == "ProcessTrainingData")
		return GetStructFromJsonString<FWorkoutStream>(jsonString, workoutStream);
	return false;
}


int32 USocketPluginExtensionLibrary::GetProcessWorkoutStateChange(FString jsonString, FPrecorWorkoutState & workoutState)
{
	FMessage msg;
	if (!GetStructFromJsonString<FMessage>(jsonString, msg))
		return -1;
	jsonString = msg.Data;
	UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *msg.Method, *msg.Data);
	if (msg.Method == "ProccessWorkoutStateChanged")
	{
		//UE_LOG(LogTemp, Warning, TEXT("USocketPluginExtensionLibrary::GetProcessWorkoutStateChange -- %d %d"), value, v);
		return GetStructFromJsonString<FPrecorWorkoutState>(jsonString, workoutState);
	}
	return false;
}


template<typename StructType>
inline bool USocketPluginExtensionLibrary::GetJsonStringFromStruct(StructType FilledStruct, FString & StringOutput)
{
	return FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template<typename StructType>
inline bool USocketPluginExtensionLibrary::GetStructFromJsonString(FString JsonString, StructType & StructOutput)
{
	return FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}