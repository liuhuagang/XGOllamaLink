// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"


#include "XGOllamaType.h"


#include "XGOllamaAysncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FXGOllamaDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message,
	FXGOllamaRespInfo, RespInfo);



UCLASS(meta = (HideThen = true))
class XGOLLAMALINK_API UXGOllamaAysncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UXGOllamaAysncAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGOllamaAysncAction();



public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGOllamaAysncAction",
		Keywords = "XG Ollama AysncAction"),
		Category = "XGOllama")
	static UXGOllamaAysncAction* XGOllamaAysncAction(UObject* WorldContextObject,
		const FString& InOllmaURL,
		const FXGOllamaReqInfo& InReqInfo);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGOllamaDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGOllamaDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGOllamaDelegate OnUpdate;

	UPROPERTY(BlueprintAssignable)
	FXGOllamaDelegate OnFail;


protected:

	virtual void Activate_Internal();

protected:

	void SendHttp(const FString& InServerURL, const FString& InContentString, TMap<FString, FString> InHeaders);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	bool HttpSream(void* Ptr, int64 Length);

	void HandleStreamData(TArray<uint8> InStreamData);

	void RecursiveProcessingStreamData();

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaRespInfo RespInfo);

	void CallOnUpdate(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaRespInfo RespInfo);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaRespInfo RespInfo);

	void RealeaseResources();

protected:

	FGuid AsyncID = FGuid::NewGuid();

	FString OllmaURL =TEXT("");

	FXGOllamaReqInfo ReqInfo;

	TArray<uint8> ErrorSteamData;

	TArray<uint8> StreamData;

	TArray<uint8> NoFixStreamData;

	FString TotalString = TEXT("");

};
