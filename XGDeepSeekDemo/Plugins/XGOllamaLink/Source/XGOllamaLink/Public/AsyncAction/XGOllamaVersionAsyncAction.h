// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGOllamaBaseAsyncAction.h"
#include "XGOllamaVersionRespType.h"

#include "XGOllamaVersionAsyncAction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FXGOllamaVersionDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message,
	FXGOllamaVersionRespInfo, RespInfo);

UCLASS(meta = (HideThen = true))
class XGOLLAMALINK_API UXGOllamaVersionAsyncAction : public UXGOllamaBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGOllamaVersionAsyncAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGOllamaVersionAsyncAction();



public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGOllamaVersionAysncAction",
		Keywords = "XG Ollama Version AysncAction"),
		Category = "XGOllama")
	static UXGOllamaVersionAsyncAction* XGOllamaAysncAction(UObject* WorldContextObject,
		const FString& InOllmaURL = TEXT("http://127.0.0.1:11434/api/version"));

	virtual void Activate() override;

public:

	UPROPERTY(BlueprintAssignable)
	FXGOllamaVersionDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGOllamaVersionDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGOllamaVersionDelegate OnFail;


protected:

	virtual void Activate_Internal() override;

protected:

	void SendHttp(const FString& InServerURL);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaVersionRespInfo RespInfo);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage, FXGOllamaVersionRespInfo RespInfo);

	void RealeaseResources();

protected:

	FString OllmaURL = TEXT("");

};

