// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//#include "Misc/FileHelper.h"
//#include <cmath>
//
//#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
//#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
//#include "Runtime/Json/Public/Dom/JsonObject.h"
//#include "SharedPointer.h"
//
//#include "EvaTTSPluginBPLibrary.h"

#include "EvaTTSActorComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EVATTS_API UEvaTTSActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UEvaTTSActorComponent() { };
	~UEvaTTSActorComponent() { };
	virtual void BeginPlay() { };

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Make Object", Keywords = "Make Object from class"), Category = "TextToSpeech")
	void MakeObject(UClass *ObjectClass, UObject* &CreatedObject)
	{
		CreatedObject = NewObject<UObject>((UObject*)GetTransientPackage(), ObjectClass);
		return;
	}

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "ParseMultiple", Keywords = "TextToSpeech Parse Multiple"), Category = "TextToSpeech")
	//UJSONHandleArray* ParseMultiple(FString JSONString, int & ElementCount, bool & Success)
	//{
	//	Success = false;
	//	ElementCount = 0;
	//	UJSONHandleArray* JSONHandleArray = NewObject<UJSONHandleArray>();
	//	try
	//	{
	//		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSONString);
	//		if (FJsonSerializer::Deserialize(JsonReader, JSONHandleArray->JSONObjectArray))
	//		{
	//			ElementCount = JSONHandleArray->JSONObjectArray.Num();
	//			Success = true;
	//		}
	//	}
	//	catch (...)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSPluginBPLibrary::ParseMultiple: Unknown exception caught while parsing string"));
	//	}
	//	return JSONHandleArray;
	//}

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "ParseFile", Keywords = "TextToSpeech Parse Content of Text File"), Category = "TextToSpeech")
	//UJSONHandleArray* ParseFile(FString FileName, int& ElementCount, bool& Success)
	//{
	//	Success = false;
	//	try
	//	{
	//		FString FileContents;

	//		FString projectDir = FPaths::ProjectDir() + FileName;
	//		if (FFileHelper::LoadFileToString(FileContents, *projectDir, FFileHelper::EHashOptions::None))
	//		{
	//			FString JSONArrayString = "[" + FileContents + "]";
	//			return UEvaTTSActorComponent::ParseMultiple(JSONArrayString, ElementCount, Success);
	//		}
	//	}
	//	catch (...)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSPluginBPLibrary::ParseFile: Unknown exception caught while parsing string"));
	//	}
	//	return nullptr;
	//}

};
