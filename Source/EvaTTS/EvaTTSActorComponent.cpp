// Fill out your copyright notice in the Description page of Project Settings.

#include "EvaTTSActorComponent.h"

UEvaTTSActorComponent* UEvaTTSActorComponent::pTTS = NULL;

// Sets default values for this component's properties
UEvaTTSActorComponent::UEvaTTSActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UEvaTTSActorComponent::pTTS = this;
	// ...
}

UEvaTTSActorComponent::~UEvaTTSActorComponent()
{
	if (pVoice)
		pVoice->Release();
	pVoice = NULL;
	::CoUninitialize();
}

// Called when the game starts
void UEvaTTSActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!TTSInit())
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent: TTSInit failed: "));
	}

}


// Called every frame
void UEvaTTSActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/****************************************************************************************
 *                               Text to Speech calls
 ****************************************************************************************/

bool UEvaTTSActorComponent::TTSInit()
{
	/*OnKafkaMessageEvent.AddDynamic(this, &UKafkaBPLibrary::OnKafkaMessage);
	OnKafkaProduceMessageEvent.AddDynamic(this, &UKafkaBPLibrary::OnKafkaProduceEvent);*/
	if (InitRan)
	{
		return true;
	}

	InitRan = true;

	if (FAILED(::CoInitialize(NULL)))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent: FAILED(::CoInitialize(NULL))"));
		return false;
	}

	pVoice = NULL;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSInit: CoCreateInstance of ISpVoice failed: "));
		return false;
	}

	cpSpCategory = NULL;

	hr = CoCreateInstance(CLSID_SpObjectTokenCategory, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpObjectTokenCategory), (void **)&cpSpCategory);

	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSInit: CoCreateInstance of ISpObjectTokenCategory failed: "));
		return false;
	}

	cpSpCategory = NULL;

	hr = CoCreateInstance(CLSID_SpObjectTokenCategory, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpObjectTokenCategory), (void **)&cpSpCategory);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSInit: Creation of ISpObjectTokenCategory failed: "));
		return false;
	}

	hr = cpSpCategory->SetId(SPCAT_VOICES, false);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSInit: Setting of id in ISpObjectTokenCategory failed: "));
		return false;
	}

	hr = CoCreateInstance(CLSID_SpStream, NULL, CLSCTX_ALL, IID_ISpStream, (void **)&pStream);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSInit: Creation of ISpStream failed: "));
		return false;
	}

	if (!pVoiceName == NULL)			// It means we have initialized before
	{
		pVoice->SetVoice(pVoiceName);		// Ok if it fails
	}

	//TTSPhonemesIndexes.Empty();
	//TTSPhonemesDurations.Empty();

	return true;

}

bool UEvaTTSActorComponent::TTSListVoices(TArray<FString>& Voices)
{
	if (!TTSInit()) return false;

	HRESULT hr = S_OK;

	if (cpSpCategory == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSListVoices cpSpCategory is NULL "));
		return false;
	}

	IEnumSpObjectTokens * cpSpEnumTokens;
	ULONG TokenCnt = 0;

	if (SUCCEEDED(hr = cpSpCategory->EnumTokens(NULL, NULL, &cpSpEnumTokens)))
	{
		ISpObjectToken * pSpTok;

		cpSpEnumTokens->GetCount(&TokenCnt);
		for (ULONG x = 0; x < TokenCnt; x++)
		{
			hr = cpSpEnumTokens->Next(1, &pSpTok, NULL);
			if (SUCCEEDED(hr))
			{
				ISpDataKey * cpKey;
				hr = pSpTok->OpenKey(L"Attributes", &cpKey);
				if (SUCCEEDED(hr))
				{
					WCHAR *psz = NULL;
					hr = cpKey->GetStringValue(L"Name", &psz);
					if (SUCCEEDED(hr))
					{
						Voices.Add(FString(psz));
					}
				}
			}
		}
	}

	return true;

}

bool UEvaTTSActorComponent::TTSGetEvents(TArray<int>& PhonemesIndexes, TArray<int>& PhonemesDurations)
{
	//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSGetEvents event: Array sizes %d, duration %d"), TTSPhonemesIndexes.Num(), TTSPhonemesDurations.Num());
	//SPEVENT event;
	//memset(&event, 0, sizeof(SPEVENT));

	////UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSGetEvents Before wait."));

	//WaitAndPumpMessagesWithTimeout(hWait, INFINITE);

	////UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSGetEvents After wait."));

	//while (S_OK == pTTS->pVoice->GetEvents(1, &event, NULL))
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSGetEvents Event found."));
	//	switch (event.eEventId)
	//	{
	//		case SPEI_PHONEME:
	//			int CurrentDuration = HIWORD(event.wParam);
	//			int CurrentPhonemeIndex = LOWORD(event.lParam);
	//			int NextPhonemeIndex = LOWORD(event.wParam);
	//			TTSPhonemesIndexes.Add(CurrentPhonemeIndex);
	//			TTSPhonemesDurations.Add(CurrentDuration);
	//			break;
	//	}

	//	SpClearEvent(&event);
	//}

	//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSGetEvents End of events."));


	PhonemesIndexes = TTSPhonemesIndexes;
	PhonemesDurations = TTSPhonemesDurations;
	//UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSGetEvents event: Array sizes at end of method %d, duration %d"), TTSPhonemesIndexes.Num(), TTSPhonemesDurations.Num());
	return false;
}

bool UEvaTTSActorComponent::TTSSetVoice(FString Name)
{
	if (!TTSInit()) return false;

	HRESULT hr = S_OK;

	if (cpSpCategory == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSetVoice cpSpCategory is NULL "));
		return false;
	}

	if (pVoice == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSetVoice pVoice is NULL "));
		return false;
	}

	IEnumSpObjectTokens * cpSpEnumTokens = NULL;
	ULONG TokenCnt = 0;

	FString Key = "Name=" + Name;

	//if (SUCCEEDED(hr = cpSpCategory->EnumTokens(L"Name=Microsoft Anna", NULL, &cpSpEnumTokens))) 
	if (SUCCEEDED(hr = cpSpCategory->EnumTokens(*Key, NULL, &cpSpEnumTokens)))
	{
		cpSpEnumTokens->GetCount(&TokenCnt);
		if (TokenCnt > 0)
		{
			hr = cpSpEnumTokens->Next(1, &pVoiceName, NULL);
			if (SUCCEEDED(hr))
			{
				hr = pVoice->SetVoice(pVoiceName);

				if (SUCCEEDED(hr))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool UEvaTTSActorComponent::TTSSetVolume(int Volume)
{
	if (!TTSInit()) return false;
	HRESULT hr = pVoice->SetVolume(Volume);

	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSetVolume method failed"));
		return false;
	}
	return true;
}

bool UEvaTTSActorComponent::TTSPause()
{
	if (!TTSInit()) return false;
	HRESULT hr = pVoice->Pause();

	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSPause method failed"));
		return false;
	}
	return true;
}

bool UEvaTTSActorComponent::TTSResume()
{
	if (!TTSInit()) return false;
	HRESULT hr = pVoice->Resume();

	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSResume method failed"));
		return false;
	}
	return true;
}

bool UEvaTTSActorComponent::TTSSaveFile(FString FileName, FString Text)
{
	if (!TTSInit()) return false;

	HRESULT hr = S_OK;

	CSpStreamFormat Format;
	ISpStreamFormat* pStreamFormat;

	pVoice->GetOutputStream(&pStreamFormat);
	Format.AssignFormat(pStreamFormat);

	FString FullName = FPaths::ProjectContentDir() + FileName;

	hr = SPBindToFile(*FullName, SPFILEMODE::SPFM_CREATE_ALWAYS, &pStream, &Format.FormatId(), Format.WaveFormatExPtr());
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSaveFile creation of bind to file failed"));
		return false;
	}

	hr = pVoice->SetOutput(pStream, true);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSaveFile set output stream ""true"" failed"));
		return false;
	}

	pVoice->Speak(*Text, SPF_ASYNC, &stream_number_);

	HANDLE hWait = pVoice->SpeakCompleteEvent();
	WaitAndPumpMessagesWithTimeout(hWait, INFINITE);

	hr = pVoice->SetOutput(pStream, false);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSaveFile set output stream ""false"" failed"));
		return false;
	}

	hr = pStream->Close();
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSaveFile close file failed"));
		return false;
	}

	hr = pStream->Release();
	//if (FAILED(hr))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSaveFile stream release failed"));
	//	return false;
	//}

	hr = pVoice->Release();
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSaveFile voice release failed"));
		return false;
	}

	::CoUninitialize();
	pStream = nullptr;
	pVoice = nullptr;

	InitRan = false;		// Let TTSInit create new objects
	return true;
}

bool UEvaTTSActorComponent::TTSSpeakStream(FString FileName)
{
	if (!TTSInit()) return false;

	HRESULT hr = S_OK;

	FString FullName = FPaths::ProjectContentDir() + FileName;

	hr = SPBindToFile(*FullName, SPFILEMODE::SPFM_OPEN_READONLY, &pStream);
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeakFile creation of bind to file failed"));
		return false;
	}

	pVoice->SpeakStream(pStream, SPEAKFLAGS::SPF_PURGEBEFORESPEAK, &stream_number_);

	hr = pStream->Close();
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeakFile close stream failed"));
		return false;
	}

	hr = pStream->Release();
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeakFile stream release failed"));
		return false;
	}

	return true;
}

bool UEvaTTSActorComponent::TTSSpeak(FString Value, bool PreparePhonemes)
{
	if (!TTSInit()) return false;

	HRESULT hr = S_OK;

	if (pVoice == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak pVoice is NULL "));
		return false;
	}

	if (PreparePhonemes)
	{
		/*ULONGLONG event_mask =
			SPFEI(SPEI_START_INPUT_STREAM) |
			SPFEI(SPEI_TTS_BOOKMARK) |
			SPFEI(SPEI_WORD_BOUNDARY) |
			SPFEI(SPEI_SENTENCE_BOUNDARY) |
			SPFEI(SPEI_PHONEME) |
			SPFEI(SPEI_END_INPUT_STREAM) |
			SPFEI(SPEI_VISEME);*/

		TTSPhonemesIndexes.Empty();
		TTSPhonemesDurations.Empty();

		ULONGLONG event_mask = SPFEI(SPEI_PHONEME);

		//ULONGLONG event_mask = SPFEI_ALL_TTS_EVENTS;

		hr = pVoice->SetInterest(event_mask, event_mask);

		//UEvaTTSActorComponent::pTTS = this;

		pVoice->SetNotifyCallbackFunction(UEvaTTSActorComponent::SpeechEventCallback, 0, 0);

	}

	hr = pVoice->SetAlertBoundary(SPEI_PHONEME);
	hr = pVoice->Speak(*Value, SPEAKFLAGS::SPF_ASYNC, &stream_number_);

	if (PreparePhonemes)
	{
		HANDLE hWait = pVoice->SpeakCompleteEvent();
		WaitAndPumpMessagesWithTimeout(hWait, INFINITE);
	}
	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak: Speak method failed"));
		return false;
	}

	return true;
}

bool UEvaTTSActorComponent::TTSPausibleSpeak(FString Value)
{
	//FString Value = "This is a long sentence to test the pause function which doesn't seemt to work.";
	if (!TTSInit()) return false;

	HRESULT hr = S_OK;

	if (pVoice == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak pVoice is NULL "));
		return false;
	}

		hr = pVoice->SetAlertBoundary(SPEI_PHONEME);
	hr = pVoice->Speak(*Value, SPEAKFLAGS::SPF_ASYNC, &stream_number_);

	if (FAILED(hr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak: Speak method failed"));
		return false;
	}

	return true;
}

//bool UEvaTTSActorComponent::TTSSpeak(FString Value)
//{
//	if (!TTSInit()) return false;
//
//	HRESULT hr = S_OK;
//
//	if (pVoice == NULL)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak pVoice is NULL "));
//		return false;
//	}
//
//	///*ULONGLONG event_mask =
//		SPFEI(SPEI_START_INPUT_STREAM) |
//		SPFEI(SPEI_TTS_BOOKMARK) |
//		SPFEI(SPEI_WORD_BOUNDARY) |
//		SPFEI(SPEI_SENTENCE_BOUNDARY) |
//		SPFEI(SPEI_PHONEME) |
//		SPFEI(SPEI_END_INPUT_STREAM) |
//		SPFEI(SPEI_VISEME);*/
//
//	//ULONGLONG event_mask = SPFEI_ALL_TTS_EVENTS;
//
//	ULONGLONG event_mask = SPFEI(SPEI_PHONEME);
//
//	pVoice->SetInterest(event_mask, event_mask);
//
//	//UEvaTTSActorComponent::pTTS = this;
//
//	pVoice->SetNotifyCallbackFunction(UEvaTTSActorComponent::SpeechEventCallback, 0, 0);
//
//	hr = pVoice->Speak(*Value, SPEAKFLAGS::SPF_ASYNC, &stream_number_);
//
//	HANDLE hWait = pVoice->SpeakCompleteEvent();
//	
//	WaitAndPumpMessagesWithTimeout(hWait, INFINITE);
//
//	if (FAILED(hr))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::TTSSpeak: Speak method failed"));
//		return false;
//	}
//
//	return true;
//}

/***********************************************************************************
 *                                   JSON Methods
 ***********************************************************************************/

UJSONHandle* UEvaTTSActorComponent::NewJSONObject()
{
	UJSONHandle* JsonHandle = NewObject<UJSONHandle>();
	JsonHandle->JSONObject = MakeShareable(new FJsonObject);
	return JsonHandle;
}

UJSONValue* UEvaTTSActorComponent::NewJSONValue()
{
	UJSONValue* JsonValue = NewObject<UJSONValue>();
	return JsonValue;
}

UJSONHandleArray* UEvaTTSActorComponent::NewJSONObjectArray()
{
	UJSONHandleArray* JSONHandleArray = NewObject<UJSONHandleArray>();
	return JSONHandleArray;
}

void UEvaTTSActorComponent::AddJSONElement(UJSONHandle* JSONHandle, FString Name, FString Value)
{
	FString NewName = Name.ReplaceEscapedCharWithChar();
	JSONHandle->JSONObject->SetStringField(NewName, Value);
}

void UEvaTTSActorComponent::AddJSONNumericElement(UJSONHandle* JSONHandle, FString Name, float Value)
{
	FString NewName = Name.ReplaceEscapedCharWithChar();
	JSONHandle->JSONObject->SetNumberField(NewName, (double)Value);
}

void UEvaTTSActorComponent::AddJSONObject(UJSONHandle* JSONHandle, FString Name, UJSONHandle* Value)
{
	FString NewName = Name.ReplaceEscapedCharWithChar();
	JSONHandle->JSONObject->SetObjectField(Name, Value->JSONObject);
}

void UEvaTTSActorComponent::AddJSONObjectToArray(UJSONHandleArray* JSONHandleArray, UJSONHandle* Value)
{
	TSharedRef<FJsonValueObject> JsonValue = MakeShareable(new FJsonValueObject(Value->JSONObject));
	JSONHandleArray->JSONObjectArray.Add(JsonValue);
}

void UEvaTTSActorComponent::AddJSONArrayToObject(UJSONHandle* JSONHandle, FString Name, UJSONHandleArray* Value)
{
	JSONHandle->JSONObject->SetArrayField(Name, Value->JSONObjectArray);
}

void UEvaTTSActorComponent::AddJSONArrayToArray(UJSONHandleArray* JSONHandleArray, FString Name, UJSONHandleArray* Value)
{
	UJSONHandle* JSONHandle = NewObject<UJSONHandle>();
	UEvaTTSActorComponent::AddJSONArrayToObject(JSONHandle, Name, Value);
	TSharedRef<FJsonValueObject> JsonValue = MakeShareable(new FJsonValueObject(JSONHandle->JSONObject));
	JSONHandleArray->JSONObjectArray.Add(JsonValue);

}

void UEvaTTSActorComponent::GetJSONElement(UJSONHandle* JSONHandle, FString Name, FString& Value)
{
	FString NewName = Name.ReplaceEscapedCharWithChar();
	Value = "";
	JSONHandle->JSONObject->TryGetStringField(NewName, Value);
}

void UEvaTTSActorComponent::GetJSONNumericElement(UJSONHandle* JSONHandle, FString Name, float& Value)
{
	FString NewName = Name.ReplaceEscapedCharWithChar();
	Value = 0;
	double Temp = 0;
	JSONHandle->JSONObject->TryGetNumberField(NewName, Temp);
	Value = (float)Temp;
}


UJSONHandle* UEvaTTSActorComponent::GetJSONObject(UJSONHandle* JSONHandle, FString Name)
{
	UJSONHandle* OutHandle = NewObject<UJSONHandle>();
	FString NewName = Name.ReplaceEscapedCharWithChar();
	OutHandle->JSONObject = JSONHandle->JSONObject->GetObjectField(NewName);
	return OutHandle;
}

UJSONHandleArray * UEvaTTSActorComponent::GetJSONArrayFromObject(UJSONHandle * JSONHandle, FString Name, int& ElementCount)
{
	UJSONHandleArray* JSONHandleArray = NewObject<UJSONHandleArray>();
	JSONHandleArray->JSONObjectArray = JSONHandle->JSONObject->GetArrayField(Name);
	ElementCount = JSONHandleArray->JSONObjectArray.Num();
	return JSONHandleArray;
}

UJSONHandleArray * UEvaTTSActorComponent::GetJSONArrayFromArray(UJSONHandleArray* JSONHandleArray, int Index, int& ElementCount)
{
	UJSONHandleArray* InnerJSONHandleArray = NewObject<UJSONHandleArray>();
	if (JSONHandleArray->JSONObjectArray[Index]->Type == EJson::Array)
	{
		InnerJSONHandleArray->JSONObjectArray = JSONHandleArray->JSONObjectArray[Index]->AsArray();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::SerializeJSONObject: Unknown exception caught while serializing object"));
		ElementCount = 0;
		return nullptr;
	}
	ElementCount = InnerJSONHandleArray->JSONObjectArray.Num();
	return InnerJSONHandleArray;
}

void UEvaTTSActorComponent::GetJSONElementMultiple(UJSONHandleArray* JSONHandleArray, int Index, FString Name, FString& Value)
{
	Value = "";
	if (Index <= JSONHandleArray->JSONObjectArray.Num() - 1)
	{
		Value = JSONHandleArray->JSONObjectArray[Index]->AsObject()->GetStringField(Name);
	}

}

void UEvaTTSActorComponent::SerializeJSONObject(UJSONHandle* JSONHandle, FString & Value, bool & Success)
{
	Value = "";
	Success = false;
	FString OutputString;
	try
	{
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JSONHandle->JSONObject.ToSharedRef(), Writer);
		Success = true;
		Value = OutputString;
		return;
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::SerializeJSONObject: Unknown exception caught while serializing object"));
	}
}

void UEvaTTSActorComponent::SerializeJSONObjectArray(UJSONHandleArray* JSONHandleArray, FString & Value, bool & Success)
{
	Value = "";
	Success = false;
	FString OutputString;
	try
	{
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JSONHandleArray->JSONObjectArray, Writer);

		Success = true;
		Value = OutputString;
		return;
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::SerializeJSONObject: Unknown exception caught while serializing object"));
	}
}


UJSONHandle* UEvaTTSActorComponent::GetJSONObjectFromArray(UJSONHandleArray* JSONHandleArray, int Index, bool& Success)
{
	UJSONHandle* JSONHandle = NewObject<UJSONHandle>();
	if (Index <= JSONHandleArray->JSONObjectArray.Num())
	{
		Success = true;
		JSONHandle->JSONObject = JSONHandleArray->JSONObjectArray[Index]->AsObject();
		return JSONHandle;
	}
	Success = false;
	return nullptr;
}


void UEvaTTSActorComponent::GetJSONObjectType(UJSONHandleArray* JSONHandleArray, int Index, EJsonType& JsonType)
{
	EJson EType = JSONHandleArray->JSONObjectArray[Index]->Type;
	EJsonType NewEnum = static_cast<EJsonType>(EType);
	JsonType = NewEnum;
}

void UEvaTTSActorComponent::GetJSONValueType(UJSONValue * JSONValue, EJsonType & JsonType)
{
	EJson EType = JSONValue->JSONValue->Type;
	EJsonType NewEnum = static_cast<EJsonType>(EType);
	JsonType = NewEnum;
}

UJSONHandle* UEvaTTSActorComponent::JSONValueAsObject(UJSONValue * JSONValue)
{
	UJSONHandle* JSONHandle = NewObject<UJSONHandle>();
	JSONHandle->JSONObject = JSONValue->JSONValue->AsObject();
	return JSONHandle;
}

UJSONHandleArray* UEvaTTSActorComponent::JSONValueAsArray(UJSONValue * JSONValue)
{
	UJSONHandleArray* JSONHandleArray = UEvaTTSActorComponent::NewJSONObjectArray();
	JSONHandleArray->JSONObjectArray = JSONValue->JSONValue->AsArray();
	return JSONHandleArray;
}

void UEvaTTSActorComponent::GetJSONArrayHandleAsArray(UJSONHandleArray * JSONHandleArray, TArray<UJSONValue*>& JSONValueArray, int & ElementCount)
{
	JSONValueArray.Empty();

	for (int x = 0; x < JSONHandleArray->JSONObjectArray.Num(); x++)
	{
		UJSONValue* JSONValue = UEvaTTSActorComponent::NewJSONValue();
		JSONValue->JSONValue = JSONHandleArray->JSONObjectArray[x];

		JSONValueArray.Add(JSONValue);
	}

	ElementCount = JSONValueArray.Num();
}


void UEvaTTSActorComponent::GetJSONObjectKeysAndTypes(UJSONHandle* JSONHandle, TMap<FString, EJsonType>& KeysAndTypes, int& ElementCount)
{
	KeysAndTypes.Empty();
	ElementCount = 0;

	for (auto& Elem : JSONHandle->JSONObject->Values)
	{
		EJson EType = Elem.Value->Type;
		EJsonType NewEnum = static_cast<EJsonType>(EType);
		KeysAndTypes.Add(Elem.Key, NewEnum);
	}

	ElementCount = KeysAndTypes.Num();
}

void UEvaTTSActorComponent::GetJSONArrayTypesAndValues(UJSONHandleArray* JSONHandleArray, TMap<EJsonType, UJSONValue*>& TypesAndValues, int& ElementCount)
{
	TypesAndValues.Empty();
	ElementCount = 0;

	for (int x = 0; x < JSONHandleArray->JSONObjectArray.Num(); x++)
	{
		UJSONValue* JSONValue = UEvaTTSActorComponent::NewJSONValue();
		JSONValue->JSONValue = JSONHandleArray->JSONObjectArray[x];

		EJson EType = JSONHandleArray->JSONObjectArray[x]->Type;
		EJsonType NewEnum = static_cast<EJsonType>(EType);

		TypesAndValues.Add(NewEnum, JSONValue);
	}

	ElementCount = TypesAndValues.Num();
}

UJSONHandleArray* UEvaTTSActorComponent::ParseFile(FString FileName, int& ElementCount, bool& Success)
{
	Success = false;
	try
	{
		FString FileContents;

		FString projectDir = FPaths::ProjectDir() + FileName;
		if (FFileHelper::LoadFileToString(FileContents, *projectDir, FFileHelper::EHashOptions::None))
		{
			FString JSONArrayString = "[" + FileContents + "]";
			return UEvaTTSActorComponent::ParseMultiple(JSONArrayString, ElementCount, Success);
		}
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::ParseFile: Unknown exception caught while parsing string"));
	}
	return nullptr;
}

bool UEvaTTSActorComponent::JSONArrayToFile(UJSONHandleArray * JSONHandleArray, FString FileName)
{
	bool Success = false;
	try
	{
		FString Value;

		UEvaTTSActorComponent::SerializeJSONObjectArray(JSONHandleArray, Value, Success);
		if (Success)
		{
			FString projectDir = FPaths::ProjectContentDir() + FileName;

			return FFileHelper::SaveStringToFile(Value, *projectDir);
		}
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::JSONArrayToFile: SerializeJSONObjectArray failed."));
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::JSONArrayToFile: Unknown exception caught while parsing string"));
	}
	return false;
}

UJSONHandleArray* UEvaTTSActorComponent::ParseMultiple(FString JSONString, int & ElementCount, bool & Success)
{
	Success = false;
	ElementCount = 0;
	UJSONHandleArray* JSONHandleArray = NewObject<UJSONHandleArray>();
	try
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSONString);
		if (FJsonSerializer::Deserialize(JsonReader, JSONHandleArray->JSONObjectArray))
		{
			ElementCount = JSONHandleArray->JSONObjectArray.Num();
			Success = true;
		}
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::ParseMultiple: Unknown exception caught while parsing string"));
	}
	return JSONHandleArray;
}

UJSONHandle* UEvaTTSActorComponent::JSONParseStringToObject(FString JSONString, bool& Success)
{
	UJSONHandle* JSONHandle = NewJSONObject();
	Success = false;
	try
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSONString);
		if (FJsonSerializer::Deserialize(JsonReader, JSONHandle->JSONObject))
		{
			Success = true;
			return JSONHandle;
		}
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::ParseString: Unknown exception caught while parsing string"));
	}
	return nullptr;
}

UJSONValue* UEvaTTSActorComponent::JSONParseStringToValue(FString JSONString, bool& Success)
{
	UJSONValue* JSONValue = NewJSONValue();
	Success = false;
	try
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSONString);
		if (FJsonSerializer::Deserialize(JsonReader, JSONValue->JSONValue))
		{
			Success = true;
			return JSONValue;
		}
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::ParseString: Unknown exception caught while parsing string"));
	}
	return nullptr;
}

/***********************************Print JSON Object*************************************/
void UEvaTTSActorComponent::PrintJSONArray(UJSONHandleArray * HandleArray)
{
	UEvaTTSActorComponent::PrintJSONArray(HandleArray->JSONObjectArray, 0);
}

void UEvaTTSActorComponent::PrintJSONArray(TArray<TSharedPtr<FJsonValue>> JSONValueArray, int level)
{

	if (level == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::PrintJSONArray: Starting"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::PrintJSONArray: Nested element:"));
	}

	int Num = JSONValueArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Number of elements: %d"), Num);

	for (int x = 0; x < Num; x++)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Printing element number: %d"), x);
		UEvaTTSActorComponent::PrintJSONValue(JSONValueArray[x], level);
	}
}

void UEvaTTSActorComponent::PrintJSONValue(TSharedPtr<FJsonValue> Value, int level)
{
	TArray<TSharedPtr<FJsonValue>> ChildArray;
	FString JsonTypeString;
	EJson JsonType = Value->Type;
	switch (JsonType)
	{
	case EJson::None:
		JsonTypeString = "None";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element type: %s."), *JsonTypeString);
		break;

	case EJson::Null:
		JsonTypeString = "Null";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element type: %s."), *JsonTypeString);
		break;

	case EJson::String:
		JsonTypeString = "String";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element type: %s. Element value: %s"), *JsonTypeString, *Value->AsString());
		break;

	case EJson::Number:
		JsonTypeString = "Number";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element value: %d"), *JsonTypeString, Value->AsNumber());
		break;

	case EJson::Boolean:
		JsonTypeString = "Boolean";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element value: %d"), *JsonTypeString, Value->AsBool() ? "true" : "false");
		break;

	case EJson::Array:
		JsonTypeString = "Array";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element type: %s."), *JsonTypeString);
		ChildArray = Value->AsArray();
		UEvaTTSActorComponent::PrintJSONArray(ChildArray, level++);
		break;

	case EJson::Object:
		JsonTypeString = "Object";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element type: %s."), *JsonTypeString);
		UEvaTTSActorComponent::PrintJSONObject(Value->AsObject(), level++);
		break;

	default:
		JsonTypeString = "Undefined";
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::Element type: %s."), *JsonTypeString);
	}
}

void UEvaTTSActorComponent::PrintJSONObject(TSharedPtr<FJsonObject> JSONObject, int level)
{
	TArray<FString> Keys;
	JSONObject->Values.GenerateKeyArray(Keys);

	for (const FString& Key : Keys)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEvaTTSActorComponent::PrintJSONObject: Processing Key: %s"), *Key);
		const TSharedPtr<FJsonValue>* Field = JSONObject->Values.Find(Key);
		UEvaTTSActorComponent::PrintJSONValue(*Field, level);
	}
}

/******************************** End of Print *************************************/

//void UEvaTTSActorComponent::AssetManagerLoadAsset(FString Name, FString Type)
//{
//	// Name: Temp
//	// Type: SoundWave
//	// Package Path: /Game 
//	// Package Name: /Game/Temp 
//	// Object Path: /Game/Temp.Temp 
//
//	//SoundWave'/Game/Eva-TTS-SpeechSynthesisIntroduction.Eva-TTS-SpeechSynthesisIntroduction'
//
//
//	FString PackagePath = "/Game";
//	FString PackageName = PackagePath + "/" + Name;
//	FString ObjectPath = PackageName + "." + Name;	
//	FString AssetName = Type + "'" + ObjectPath + "'";
//
//	UAssetManager& AssetManager = UAssetManager::Get();
//
//	//const FPrimaryAssetId AssetId = FPrimaryAssetId(FName(*Type), FName(*AssetName));
//	//const FAssetData AssetData = FAssetData(FName(*PackageName), FName(*PackagePath), FName(*AssetName), FName(*Type));
//
//	FAssetBundleData AssetBundle;
//	AssetBundle.SetFromAssetData(FAssetData(FName(*PackageName), FName(*PackagePath), FName(*AssetName), FName(*Type)));
//
//	FSoftObjectPath SoftObjectPath(ObjectPath);
//
//	// Register a dynamic Asset 
//	AssetManager.AddDynamicAsset(FPrimaryAssetId(FName(*Type), FName(*AssetName)), SoftObjectPath, AssetBundle);
//
//	TArray<FName> LoadBundle;
//	LoadBundle.Add(FName(*AssetName));
//
//	// Start preloading
//	AssetManager.LoadPrimaryAsset(FPrimaryAssetId(FName(*Type), FName(*AssetName)), LoadBundle);
//
//}