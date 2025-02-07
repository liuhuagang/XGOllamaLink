// Copyright 2025 Xiao Gang. All Rights Reserved.

#include "XGOllamaAysncAction.h"

#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h"

#include "LogXGOllama.h"

UXGOllamaAysncAction::UXGOllamaAysncAction(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{

}

UXGOllamaAysncAction::~UXGOllamaAysncAction()
{
	RealeaseResources();
}


UXGOllamaAysncAction* UXGOllamaAysncAction::XGOllamaAysncAction(UObject* WorldContextObject,
const FString& InOllmaURL, 
const FXGOllamaReqInfo& InReqInfo)
{
	UXGOllamaAysncAction* AsyncAction = NewObject<UXGOllamaAysncAction>();

	AsyncAction->OllmaURL = InOllmaURL;
	AsyncAction->ReqInfo = InReqInfo;

	AsyncAction->RegisterWithGameInstance(WorldContextObject);

	return AsyncAction;
}

void UXGOllamaAysncAction::Activate()
{
	Super::Activate();

	Then.Broadcast(AsyncID, false, 
	TEXT("XGOllamaAysncAction is just started,please wait to be finished!"), 
		FXGOllamaRespInfo());

}

void UXGOllamaAysncAction::Activate_Internal()
{
	UE_LOG(LogXGOllama, Display, TEXT("[%s],AsyncID:[%s],Begin to execute XGOllama AysncAction  "),
	*FString(__FUNCTION__),*(AsyncID.ToString()));

	if (OllmaURL.IsEmpty())
	{
		CallOnFail(AsyncID,false,TEXT("OllmaURL is Null!!! please input URL"), FXGOllamaRespInfo());

		RealeaseResources();

		return;
	}


	FString ConentString = ReqInfo.ToJsonString();

	TMap<FString, FString> OutHeaders;

	OutHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));

	UE_LOG(LogXGOllama, Verbose, TEXT("[%s],[%s]"), *FString(__FUNCTION__), *ConentString);

	SendHttp(OllmaURL, ConentString, OutHeaders);

}

void UXGOllamaAysncAction::SendHttp(const FString& InServerURL, const FString& InContentString, TMap<FString, FString> InHeaders)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UXGOllamaAysncAction::OnHttpRespReceived);

	FHttpRequestStreamDelegate Delegate;
	Delegate.BindUObject(this, &UXGOllamaAysncAction::HttpSream);

	if (ReqInfo.stream)
	{
		Request->SetResponseBodyReceiveStreamDelegate(Delegate);
	}

	Request->SetURL(InServerURL);

	for (auto& Tmp : InHeaders)
	{
		Request->SetHeader(Tmp.Key, Tmp.Value);
	}

	Request->SetVerb("Post");

	Request->SetContentAsString(InContentString);

	Request->ProcessRequest();
}

void UXGOllamaAysncAction::OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	UE_LOG(LogXGOllama, Display, TEXT("[%s],AsyncID:[%s],Receive Ollma HttpResonpse"), *FString(__FUNCTION__), *(AsyncID.ToString()));

	FString ResponseJson = TEXT("");

	if (!HttpResponse.IsValid())
	{
		FXGOllamaRespInfo HttpError;
		HttpError.bReqStream = ReqInfo.stream;
		HttpError.bFinish = true;

		UE_LOG(LogXGOllama, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

		CallOnFail(AsyncID, false, TEXT("Http Failed,Message:") + ResponseJson, HttpError);

		RealeaseResources();

		return;
	}

	ResponseJson = HttpResponse->GetContentAsString();

	UE_LOG(LogXGOllama, Verbose, TEXT("[%s],[%s]"), *FString(__FUNCTION__), *ResponseJson);

	if (bSucceeded && HttpRequest->GetStatus() == EHttpRequestStatus::Succeeded && HttpResponse->GetResponseCode() == 200)
	{

		if (ReqInfo.stream)
		{


		}
		else
		{

			FXGOllamaRespFinalMessage NoStreamRespMessage;
			FJsonObjectConverter::JsonObjectStringToUStruct(ResponseJson, &NoStreamRespMessage);

			FXGOllamaRespInfo RespInfo;
			RespInfo.bFinish = false;
			RespInfo.bReqStream = ReqInfo.stream;
			RespInfo.FinalInfo = NoStreamRespMessage;

			CallOnSuccess(AsyncID, true, NoStreamRespMessage.response, RespInfo);


		}
	}
	else
	{

		if (ReqInfo.stream)
		{
			FUTF8ToTCHAR ErrorJsonString((const ANSICHAR*)ErrorSteamData.GetData(), ErrorSteamData.Num());

			FString ErrorString(ErrorJsonString.Length(), ErrorJsonString.Get());

			FXGOllamaRespInfo HttpError;
			HttpError.bReqStream = ReqInfo.stream;
			HttpError.bFinish = true;

			UE_LOG(LogXGOllama, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ErrorString);

			CallOnFail(AsyncID, false, TEXT("Http Failed,Message:") + ErrorString, HttpError);


		}
		else
		{

	

			FXGOllamaRespInfo HttpError;
			HttpError.bReqStream = ReqInfo.stream;
			HttpError.bFinish = true;

			UE_LOG(LogXGOllama, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

			CallOnFail(AsyncID, false, TEXT("Http Failed,Message:") + ResponseJson, HttpError);
		}
	}

	RealeaseResources();
}

bool UXGOllamaAysncAction::HttpSream(void* Ptr, int64 Length)
{
	TArray<uint8> TempStreamData;

	TempStreamData.Append((uint8*)Ptr, Length);

	UXGOllamaAysncAction* TestPtr = this;

	if (TestPtr)
	{
		AsyncTask(ENamedThreads::GameThread, [TempStreamData, TestPtr]() {

			if (TestPtr)
			{
				TestPtr->HandleStreamData(TempStreamData);
			}

			});
	}

	return true;
}

void UXGOllamaAysncAction::HandleStreamData(TArray<uint8> InStreamData)
{
	if (IsEngineExitRequested())
	{
		return;
	}


	FUTF8ToTCHAR UTF8String((const ANSICHAR*)InStreamData.GetData(), InStreamData.Num());

	FString OriginIndexedJson(UTF8String.Length(), UTF8String.Get());

	FString IndexedJson(UTF8String.Length(), UTF8String.Get());

	TSharedPtr<FJsonObject> TextJsonObject;
	TSharedRef<TJsonReader<TCHAR>>TextJsonReader = TJsonReaderFactory<TCHAR>::Create(IndexedJson);
	bool IsDeserialize = FJsonSerializer::Deserialize(TextJsonReader, TextJsonObject);

	if (IsDeserialize && TextJsonObject->TryGetField(TEXT("error")))
	{
		ErrorSteamData = InStreamData;
		return;
	}



	StreamData.Append(InStreamData);

	RecursiveProcessingStreamData();
}

void UXGOllamaAysncAction::RecursiveProcessingStreamData()
{
	int32 RecoredIndex = -1;

	for (size_t Index = 0; Index < StreamData.Num(); Index++)
	{
		if (StreamData[Index] == 10)
		{
			RecoredIndex = Index;
			break;
		}
	}

	if (RecoredIndex != -1)
	{
		TArray<uint8> HandleStreamData;
		HandleStreamData.Append(StreamData.GetData(), RecoredIndex);

		StreamData.RemoveAt(0, RecoredIndex + 1);

		FUTF8ToTCHAR HandleString((const ANSICHAR*)HandleStreamData.GetData(), HandleStreamData.Num());

		FString OriginHandleJson(HandleString.Length(), HandleString.Get());
		FString HandleJson(HandleString.Length(), HandleString.Get());

		HandleJson.RemoveFromStart(TEXT("data:"));

		UE_LOG(LogXGOllama, Verbose, TEXT("[%s], Stream  data Apeend ,JsonStr:[%s]"), *FString(__FUNCTION__), *OriginHandleJson);

		if (HandleJson.Contains(TEXT("\n")))
		{
			UE_LOG(LogXGOllama, Error, TEXT("[%s],Fatal Error  Stream  data Apeend Wroing!!!,JsonStr:[%s]"), *FString(__FUNCTION__), *OriginHandleJson);
		}
		FXGOllamaRespMiddleMessageStreamInfo StreamMiddleMessage;

		FJsonObjectConverter::JsonObjectStringToUStruct(HandleJson, &StreamMiddleMessage);

		if (StreamMiddleMessage.done)
		{
			UE_LOG(LogXGOllama, Verbose, TEXT("[%s],Stream  data Finish!!!,JsonStr:[%s]"), *FString(__FUNCTION__), *OriginHandleJson);

			FXGOllamaRespFinalMessage FinalMessage;

			FJsonObjectConverter::JsonObjectStringToUStruct(HandleJson, &FinalMessage);


			FXGOllamaRespInfo RespInfo;

			RespInfo.bReqStream = true;
			RespInfo.bFinish = true;

			RespInfo.FinalInfo = FinalMessage;

			TotalString += RespInfo.FinalInfo.response;

			CallOnSuccess(AsyncID, true, TotalString, RespInfo);

			RecursiveProcessingStreamData();


			return;
		}

		FXGOllamaRespInfo RespInfo;

		RespInfo.bReqStream = true;
		RespInfo.bFinish = false;

		RespInfo.MiddleInfo = StreamMiddleMessage;

		TotalString += RespInfo.MiddleInfo.response;

		CallOnUpdate(AsyncID, true, RespInfo.MiddleInfo.response, RespInfo);

		RecursiveProcessingStreamData();

	}
}

void UXGOllamaAysncAction::CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaRespInfo RespInfo)
{
	FXGOllamaDelegate TempDelegate = OnSuccess;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, RespInfo);


		});
}

void UXGOllamaAysncAction::CallOnUpdate(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaRespInfo RespInfo)
{
	FXGOllamaDelegate TempDelegate = OnUpdate;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, RespInfo);


		});
}

void UXGOllamaAysncAction::CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaRespInfo RespInfo)
{
	FXGOllamaDelegate TempDelegate = OnFail;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, RespInfo);


		});
}

void UXGOllamaAysncAction::RealeaseResources()
{
	Then.Clear();

	OnSuccess.Clear();

	OnUpdate.Clear();

	OnFail.Clear();

	OllmaURL.Empty();

	ReqInfo = FXGOllamaReqInfo();

	ErrorSteamData.Empty();

	StreamData.Empty();

	NoFixStreamData.Empty();

	TotalString.Empty();

	SetReadyToDestroy();
}
