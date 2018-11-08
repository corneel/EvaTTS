// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

#pragma once

#include "Engine/AssetManager.h"
#include "AssetData.h"
#include "AssetBundleData.h"
#include "Misc/FileHelper.h"
#include <cmath>

#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "SharedPointer.h"

/*************************************** Windows Stuff ***************************************************/

#include "AllowWindowsPlatformTypes.h"
#include "AllowWindowsPlatformAtomics.h"

#pragma warning(push)
#pragma warning(disable: 4191) // warning C4191: 'type cast' : unsafe conversion
#pragma warning(disable: 4996) // error C4996: 'GetVersionEx': was declared deprecated

#define WIN32_LEAN_AND_MEAN

// atltransactionmanager.h doesn't use the W equivalent functions, use this workaround
#ifndef DeleteFile
#define DeleteFile DeleteFileW
#endif
#ifndef MoveFile
#define MoveFile MoveFileW
#endif
#ifndef LoadString
#define LoadString LoadStringW
#endif
#ifndef GetMessage
#define GetMessage GetMessageW
#endif

#include <sapi.h>
#include <sphelper.h>

#undef DeleteFile
#undef MoveFile

#pragma warning(pop)

#include "HideWindowsPlatformTypes.h"

/*************************************** Windows Stuff ***************************************************/


#include "Kismet/BlueprintFunctionLibrary.h"
#include "EvaTTSPluginBPLibrary.generated.h"

UENUM(BlueprintType, Category = "TextToSpeech")
enum class EJsonType : uint8
{
	None	UMETA(DisplayName = "None"),
	Null	UMETA(DisplayName = "Null"),
	String	UMETA(DisplayName = "String"),
	Number	UMETA(DisplayName = "Number"),
	Boolean UMETA(DisplayName = "Boolean"),
	Array	UMETA(DisplayName = "Array"),
	Object	UMETA(DisplayName = "Object")
};

UCLASS(BlueprintType)
class UJSONValue : public UObject
{

	GENERATED_BODY()
public:
	TSharedPtr<FJsonValue> JSONValue;
};

UCLASS(BlueprintType)
class UJSONHandle : public UObject
{
	GENERATED_BODY()
public:
	TSharedPtr<FJsonObject> JSONObject;
};

UCLASS(BlueprintType)
class UJSONHandleArray : public UObject
{
	GENERATED_BODY()
public:
	TArray<TSharedPtr<FJsonValue>> JSONObjectArray;
};

USTRUCT(BlueprintType)
struct FSoundIndexArrayStruct
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "Student") int32 Age;
	UPROPERTY(BlueprintReadWrite, Category = "Student") FString Name;
};

UCLASS(BlueprintType)
class UJSONStructArray : public UObject
{
	GENERATED_BODY()
public:
	TArray<FSoundIndexArrayStruct> SoundIndex;
};


UCLASS(BlueprintType, Blueprintable)
class UEvaTTSPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

		UEvaTTSPluginBPLibrary();

	/*************************************************** SAPI TTS Methods *************************************************/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSSetVoice", Keywords = "Set Voice TTS"), Category = "TextToSpeech")
		bool TTSSetVoice(FString Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSSetVolume", Keywords = "Set Volume TTS"), Category = "TextToSpeech")
		bool TTSSetVolume(int Volume);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSPause", Keywords = "Pause TTS"), Category = "TextToSpeech")
		bool TTSPause();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSResume", Keywords = "Resume TTS"), Category = "TextToSpeech")
		bool TTSResume();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSSaveFile", Keywords = "Save File TTS"), Category = "TextToSpeech")
		bool TTSSaveFile(FString FileName, FString Text);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSSpeak", Keywords = "Speak TTS"), Category = "TextToSpeech")
		bool TTSSpeak(FString Value, bool PreparePhonemes = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSPausibleSpeak", Keywords = "Speak Pausible Speak TTS"), Category = "TextToSpeech")
		bool TTSPausibleSpeak(FString Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSSpeakFile", Keywords = "Speak TTS File Stream"), Category = "TextToSpeech")
		bool TTSSpeakStream(FString Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSListVoices", Keywords = "ListVoices TTS"), Category = "TextToSpeech")
		bool TTSListVoices(TArray<FString>& Voices);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTSGetEvents", Keywords = "Get Events TTS"), Category = "TextToSpeech")
		bool TTSGetEvents(TArray<int>& TTSPhonemesIndexes, TArray<int>& TTSPhonemesDurations);

	/**************************************JSON Methods**************************************/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NewJSONObject", Keywords = "TextToSpeech New JSON Object"), Category = "TextToSpeech")
		static UJSONHandle* NewJSONObject();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NewJSONValue", Keywords = "TextToSpeech New JSON Value"), Category = "TextToSpeech")
		static UJSONValue* NewJSONValue();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NewJSONObjectArray", Keywords = "TextToSpeech New JSON Object Array"), Category = "TextToSpeech")
		static UJSONHandleArray* NewJSONObjectArray();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddJSONElement", Keywords = "TextToSpeech Add JSON Element String"), Category = "TextToSpeech")
		static void AddJSONElement(UJSONHandle* JSONHandle, FString Name, FString Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddJSONNumericElement", Keywords = "TextToSpeech Add JSON Numeric Element"), Category = "TextToSpeech")
		static void AddJSONNumericElement(UJSONHandle* JSONHandle, FString Name, float Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddJSONObject", Keywords = "TextToSpeech Add JSON Object"), Category = "TextToSpeech")
		static void AddJSONObject(UJSONHandle* JSONHandle, FString Name, UJSONHandle* Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddJSONObjectToArray", Keywords = "TextToSpeech Add JSON Object To Array"), Category = "TextToSpeech")
		static void AddJSONObjectToArray(UJSONHandleArray* JSONHandleArray, UJSONHandle* Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddJSONArrayToObject", Keywords = "TextToSpeech Add Array to JSON Object"), Category = "TextToSpeech")
		static void AddJSONArrayToObject(UJSONHandle* JSONHandle, FString Name, UJSONHandleArray* Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddJSONArrayToArray", Keywords = "TextToSpeech Add Array to JSON Array"), Category = "TextToSpeech")
		static void AddJSONArrayToArray(UJSONHandleArray* JSONHandleArray, FString Name, UJSONHandleArray* Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONElement", Keywords = "TextToSpeech Get JSON Element"), Category = "TextToSpeech")
		static void GetJSONElement(UJSONHandle* JSONHandle, FString Name, FString& Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONNumericElement", Keywords = "TextToSpeech Get JSON Numeric Element"), Category = "TextToSpeech")
		static void GetJSONNumericElement(UJSONHandle* JSONHandle, FString Name, float& Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONObject", Keywords = "TextToSpeech Get JSON Object"), Category = "TextToSpeech")
		static UJSONHandle* GetJSONObject(UJSONHandle* JSONHandle, FString Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONArrayFromObject", Keywords = "TextToSpeech Get JSON Object Array"), Category = "TextToSpeech")
		static UJSONHandleArray* GetJSONArrayFromObject(UJSONHandle* JSONHandle, FString Name, int& ElementCount);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONArrayFromArray", Keywords = "TextToSpeech Get JSON Object Array"), Category = "TextToSpeech")
		static UJSONHandleArray* GetJSONArrayFromArray(UJSONHandleArray* JSONHandleArray, int Index, int& ElementCount);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONElement", Keywords = "TextToSpeech Get JSON Element from object array"), Category = "TextToSpeech")
		static void GetJSONElementMultiple(UJSONHandleArray* JSONHandleArray, int Index, FString Name, FString& Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SerializeJSONObject", Keywords = "TextToSpeech Serialize JSON Object"), Category = "TextToSpeech")
		static void SerializeJSONObject(UJSONHandle* JSONHandle, FString& Value, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SerializeJSONObjectArray", Keywords = "TextToSpeech Serialize JSON Object Array"), Category = "TextToSpeech")
		static void SerializeJSONObjectArray(UJSONHandleArray* JSONHandleArray, FString& Value, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ParseString", Keywords = "TextToSpeech Parse String to Object"), Category = "TextToSpeech")
		static UJSONHandle* JSONParseStringToObject(FString JSONString, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ParseString", Keywords = "TextToSpeech Parse String to Value"), Category = "TextToSpeech")
		static UJSONValue* JSONParseStringToValue(FString JSONString, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ParseMultiple", Keywords = "TextToSpeech Parse Multiple"), Category = "TextToSpeech")
		static UJSONHandleArray* ParseMultiple(FString JSONString, int& ElementCount, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ParseFile", Keywords = "TextToSpeech Parse Content of Text File"), Category = "TextToSpeech")
		static UJSONHandleArray* ParseFile(FString FileName, int& ElementCount, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JSONArrayToFile", Keywords = "TextToSpeech Save JSON Object Array to Text File"), Category = "TextToSpeech")
		static bool JSONArrayToFile(UJSONHandleArray* JSONHandleArray, FString FileName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONObjectFromArray", Keywords = "TextToSpeech Get JSONObject From Array"), Category = "TextToSpeech")
		static UJSONHandle* GetJSONObjectFromArray(UJSONHandleArray* JSONHandleArray, int Index, bool& Success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PrintJSONArray", Keywords = "TextToSpeech Print a JSONArray"), Category = "TextToSpeech")
		static void PrintJSONArray(UJSONHandleArray* JSONHandleArray);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONObjectType", Keywords = "TextToSpeech Get JSON Object Type"), Category = "TextToSpeech")
		static void GetJSONObjectType(UJSONHandleArray* JSONHandleArray, int Index, EJsonType& JsonType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONValueType", Keywords = "TextToSpeech Get JSON Value Type"), Category = "TextToSpeech")
		static void GetJSONValueType(UJSONValue* JSONValue, EJsonType& JsonType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JSONValueAsObject", Keywords = "TextToSpeech Get JSON Value As Object"), Category = "TextToSpeech")
		static UJSONHandle* JSONValueAsObject(UJSONValue* JSONValue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JSONValueAsArray", Keywords = "TextToSpeech Get JSON Value as Array"), Category = "TextToSpeech")
		static UJSONHandleArray* JSONValueAsArray(UJSONValue* JSONValue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONArrayHandleAsArray", Keywords = "TextToSpeech Get JSON Array Handle as Array"), Category = "TextToSpeech")
		static void GetJSONArrayHandleAsArray(UJSONHandleArray* JSONHandleArray, TArray<UJSONValue*>& JSONValueArray, int& ElementCount);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONObjectKeysAndTypes", Keywords = "TextToSpeech Get JSON Object Keys and Types"), Category = "TextToSpeech")
		static void GetJSONObjectKeysAndTypes(UJSONHandle* JSONHandle, TMap<FString, EJsonType>& KeysAndTypes, int& ElementCount);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJSONArrayTypesAndValues", Keywords = "TextToSpeech Get JSON Types and Values"), Category = "TextToSpeech")
		static void GetJSONArrayTypesAndValues(UJSONHandleArray* JSONHandleArray, TMap<EJsonType, UJSONValue*>& TypesAndValues, int& ElementCount);

	private:

	static void PrintJSONArray(TArray<TSharedPtr<FJsonValue>> JSONHandleArray, int level);
	static void PrintJSONValue(TSharedPtr<FJsonValue> Value, int level);
	static void PrintJSONObject(TSharedPtr<FJsonObject> JSONObject, int level);

	bool TTSInit();

	/***************************************** SAPI TTS Events ************************************************/
	static void __stdcall SpeechEventCallback(WPARAM w_param, LPARAM l_param)
	{
		//std::cout << "callback function\n";
		pTTS->OnSpeechEvent();
	}

	void OnSpeechEvent1()
	{

		// TTS

		FString utterance_ = "";
		int prefix_len_ = 0;
		SPVOICESTATUS eventStatus;
		int char_position_ = 0;

		SPEVENT event;
		while (S_OK == pTTS->pVoice->GetEvents(1, &event, NULL)) {
			if (event.ulStreamNum != stream_number_)
				continue;

			switch (event.eEventId) {
			case SPEI_START_INPUT_STREAM:
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_START_INPUT_STREAM"));
				break;

			case SPEI_END_INPUT_STREAM:
				char_position_ = utterance_.Len();
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_END_INPUT_STREAM"));
				break;

			case SPEI_TTS_BOOKMARK:
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_TTS_BOOKMARK"));
				break;

			case SPEI_WORD_BOUNDARY:
				char_position_ = static_cast<ULONG>(event.lParam) - prefix_len_;
				ULONG start, end;
				pTTS->pVoice->GetStatus(&eventStatus, NULL);
				start = eventStatus.ulInputWordPos;
				end = eventStatus.ulInputWordLen;
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_WORD_BOUNDARY. Start: %d, length: %d."), eventStatus.ulInputWordPos, eventStatus.ulInputWordLen);
				break;

			case SPEI_SENTENCE_BOUNDARY:
				char_position_ = static_cast<ULONG>(event.lParam) - prefix_len_;
				pTTS->pVoice->GetStatus(&eventStatus, NULL);
				start = eventStatus.ulInputSentPos;
				end = eventStatus.ulInputSentLen;
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_SENTENCE_BOUNDARY. Start: %d, length: %d."), eventStatus.ulInputSentPos, eventStatus.ulInputSentLen);
				break;

			case SPEI_VISEME:
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_VISEME"));
				break;

			case SPEI_PHONEME:
				int CurrentDuration = HIWORD(event.wParam);
				int CurrentPhonemeIndex = LOWORD(event.lParam);
				int NextPhonemeIndex = LOWORD(event.wParam);
				TTSPhonemesIndexes.Add(CurrentPhonemeIndex);
				//TTSPhonemesIndexes.Add(NextPhonemeIndex);
				TTSPhonemesDurations.Add(CurrentDuration);

				UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::OnSpeechEvent: SPEI_PHONEME. Current phoneme index %d, duration %d"), CurrentPhonemeIndex, CurrentDuration);

				break;
			}
		}
	}

	HRESULT WaitAndPumpMessagesWithTimeout1(HANDLE hWaitHandle, DWORD dwMilliseconds)
	{
		HRESULT hr = S_OK;
		BOOL fContinue = true;

		while (fContinue)
		{
			DWORD dwWaitId = ::MsgWaitForMultipleObjectsEx(1, &hWaitHandle, dwMilliseconds, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
			switch (dwWaitId)
			{
			case WAIT_OBJECT_0:
			{
				fContinue = false;
			}
			break;

			case WAIT_OBJECT_0 + 1:
			{
				MSG Msg;
				while (::PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
				{
					::TranslateMessage(&Msg);
					::DispatchMessage(&Msg);
				}
			}
			break;

			case WAIT_TIMEOUT:
			{
				hr = S_FALSE;
				fContinue = false;
			}
			break;
			default:// Unexpected error
			{
				fContinue = false;
				hr = E_FAIL;
			}
			break;
			}
		}
		return hr;
	}

	void OnSpeechEvent()
	{

		// TTS

		FString utterance_ = "";
		int prefix_len_ = 0;
		SPVOICESTATUS eventStatus;
		int char_position_ = 0;

		SPEVENT event;
		while (S_OK == pTTS->pVoice->GetEvents(1, &event, NULL)) {
			if (event.ulStreamNum != stream_number_)
				continue;

			switch (event.eEventId) {
			case SPEI_START_INPUT_STREAM:
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_START_INPUT_STREAM"));
				break;

			case SPEI_END_INPUT_STREAM:
				char_position_ = utterance_.Len();
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_END_INPUT_STREAM"));
				break;

			case SPEI_TTS_BOOKMARK:
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_TTS_BOOKMARK"));
				break;

			case SPEI_WORD_BOUNDARY:
				char_position_ = static_cast<ULONG>(event.lParam) - prefix_len_;
				ULONG start, end;
				pTTS->pVoice->GetStatus(&eventStatus, NULL);
				start = eventStatus.ulInputWordPos;
				end = eventStatus.ulInputWordLen;
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_WORD_BOUNDARY. Start: %d, length: %d."), eventStatus.ulInputWordPos, eventStatus.ulInputWordLen);
				break;

			case SPEI_SENTENCE_BOUNDARY:
				char_position_ = static_cast<ULONG>(event.lParam) - prefix_len_;
				pTTS->pVoice->GetStatus(&eventStatus, NULL);
				start = eventStatus.ulInputSentPos;
				end = eventStatus.ulInputSentLen;
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_SENTENCE_BOUNDARY. Start: %d, length: %d."), eventStatus.ulInputSentPos, eventStatus.ulInputSentLen);
				break;

			case SPEI_VISEME:
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_VISEME"));
				break;

			case SPEI_PHONEME:
				int CurrentDuration = HIWORD(event.wParam);
				int CurrentPhonemeIndex = LOWORD(event.lParam);
				int NextPhonemeIndex = LOWORD(event.wParam);
				TTSPhonemesIndexes.Add(CurrentPhonemeIndex);
				//TTSPhonemesIndexes.Add(NextPhonemeIndex);
				TTSPhonemesDurations.Add(CurrentDuration);

				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_PHONEME. Current phoneme index %d, duration %d"), CurrentPhonemeIndex, CurrentDuration);
				//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak event: SPEI_PHONEME. Next phoneme index %d"), NextPhonemeIndex);

				break;
			}
		}
	}

	HRESULT WaitAndPumpMessagesWithTimeout(HANDLE hWaitHandle, DWORD dwMilliseconds)
	{
		HRESULT hr = S_OK;
		BOOL fContinue = true;

		while (fContinue)
		{
			DWORD dwWaitId = ::MsgWaitForMultipleObjectsEx(1, &hWaitHandle, dwMilliseconds, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
			switch (dwWaitId)
			{
			case WAIT_OBJECT_0:
			{
				fContinue = false;
			}
			break;

			case WAIT_OBJECT_0 + 1:
			{
				MSG Msg;
				while (::PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
				{
					::TranslateMessage(&Msg);
					::DispatchMessage(&Msg);
				}
			}
			break;

			case WAIT_TIMEOUT:
			{
				hr = S_FALSE;
				fContinue = false;
			}
			break;
			default:// Unexpected error
			{
				fContinue = false;
				hr = E_FAIL;
			}
			break;
			}
		}
		return hr;
	}
	/***************************************** SAPI TTS Events ************************************************/

	TArray<int> TTSPhonemesIndexes;
	TArray<int> TTSPhonemesDurations;

	static UEvaTTSPluginBPLibrary* pTTS;
	ISpVoice * pVoice = NULL;
	ISpStream * pStream = NULL;
	ISpObjectToken * pVoiceName = NULL;
	ULONG stream_number_;

	ISpObjectTokenCategory * cpSpCategory = NULL;
	FString Name;
	bool InitRan = false;
};
