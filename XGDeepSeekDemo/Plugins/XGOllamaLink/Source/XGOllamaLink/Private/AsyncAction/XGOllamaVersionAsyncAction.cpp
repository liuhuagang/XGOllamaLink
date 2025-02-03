// Copyright 2025 Xiao Gang. All Rights Reserved.

#include "XGOllamaVersionAsyncAction.h"

#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h"

#include "LogXGOllama.h"

UXGOllamaVersionAsyncAction::UXGOllamaVersionAsyncAction(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{

}

UXGOllamaVersionAsyncAction::~UXGOllamaVersionAsyncAction()
{
	RealeaseResources();
}

UXGOllamaVersionAsyncAction* UXGOllamaVersionAsyncAction::XGOllamaAysncAction(UObject* WorldContextObject,
const FString& InOllmaURL)
{
	UXGOllamaVersionAsyncAction* AsyncAction = NewObject<UXGOllamaVersionAsyncAction>();

	AsyncAction->OllmaURL = InOllmaURL;

	AsyncAction->RegisterWithGameInstance(WorldContextObject);

	return AsyncAction;
}

void UXGOllamaVersionAsyncAction::Activate()
{
	Super::Activate();
	 
	Then.Broadcast(AsyncID, false,
		TEXT("XGOllamaVersionAsyncAction is just started,please wait to be finished!"),
		FXGOllamaVersionRespInfo());
}

void UXGOllamaVersionAsyncAction::Activate_Internal()
{
	UE_LOG(LogXGOllama, Display, TEXT("[%s],AsyncID:[%s],Begin to execute XGOllama AysncAction  "),
		*FString(__FUNCTION__), *(AsyncID.ToString()));

	if (OllmaURL.IsEmpty())
	{
		CallOnFail(AsyncID, false, TEXT("OllmaURL is Null!!! please input URL"), FXGOllamaVersionRespInfo());

		RealeaseResources();

		return;
	}


	UE_LOG(LogXGOllama, Verbose, TEXT("[%s],[%s]"), *FString(__FUNCTION__), TEXT("Begin to request Ollama Version"));

	SendHttp(OllmaURL);


}

void UXGOllamaVersionAsyncAction::SendHttp(const FString& InServerURL)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UXGOllamaVersionAsyncAction::OnHttpRespReceived);

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));


	Request->SetURL(InServerURL);

	Request->SetVerb("GET");

	Request->ProcessRequest();

}

void UXGOllamaVersionAsyncAction::OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	UE_LOG(LogXGOllama, Display, TEXT("[%s],AsyncID:[%s],Receive Ollma HttpResonpse"), *FString(__FUNCTION__), *(AsyncID.ToString()));

	FString ResponseJson = TEXT("");

	if (!HttpResponse.IsValid())
	{
		FXGOllamaVersionRespInfo HttpRespError;

		ResponseJson =TEXT("HttpResponse is Null!Please check your URL is right?");

		UE_LOG(LogXGOllama, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

		CallOnFail(AsyncID, false, TEXT("Http Failed,Message:") + ResponseJson, HttpRespError);

		RealeaseResources();

		return ;
	}

	ResponseJson = HttpResponse->GetContentAsString();

	UE_LOG(LogXGOllama, Verbose, TEXT("[%s],[%s]"), *FString(__FUNCTION__), *ResponseJson);

	if (bSucceeded && HttpRequest->GetStatus() == EHttpRequestStatus::Succeeded && HttpResponse->GetResponseCode() == 200)
	{

		FXGOllamaVersionRespInfo RespInfo;
		FJsonObjectConverter::JsonObjectStringToUStruct(ResponseJson, &RespInfo);

		CallOnSuccess(AsyncID, true, RespInfo.version, RespInfo);

	}
	else
	{

		FXGOllamaVersionRespInfo HttpError;

		UE_LOG(LogXGOllama, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

		CallOnFail(AsyncID, false, TEXT("Http Failed,Message:") + ResponseJson, HttpError);
	}


	RealeaseResources();


}

void UXGOllamaVersionAsyncAction::CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaVersionRespInfo RespInfo)
{
	FXGOllamaVersionDelegate TempDelegate = OnSuccess;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, RespInfo);


		});
}

void UXGOllamaVersionAsyncAction::CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaVersionRespInfo RespInfo)
{
	FXGOllamaVersionDelegate TempDelegate = OnSuccess;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, RespInfo);


		});

}

void UXGOllamaVersionAsyncAction::RealeaseResources()
{
	SetReadyToDestroy();
}
