// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "XGOllamaType.generated.h"


USTRUCT(BlueprintType)
struct XGOLLAMALINK_API FXGOllamaReqInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	model = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	prompt = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	bool stream = false;

	FString ToJsonString();

};




USTRUCT(BlueprintType)
struct XGOLLAMALINK_API FXGOllamaRespMiddleMessageStreamInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	model = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	created_at = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	response = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	bool done =false;
};

USTRUCT(BlueprintType)
struct XGOLLAMALINK_API FXGOllamaRespFinalMessage
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	model = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	created_at = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	response = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	bool done = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	done_rease = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	TArray<int32> context ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	int64	total_duration = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	int64	load_duration = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	int64	prompt_eval_count = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	int64	prompt_eval_duration = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	int64	eval_count = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	int64	eval_duration = -1;

};






USTRUCT(BlueprintType)
struct XGOLLAMALINK_API FXGOllamaRespInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	bool    bReqStream = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	bool	bFinish =false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FXGOllamaRespMiddleMessageStreamInfo MiddleInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FXGOllamaRespFinalMessage FinalInfo;

};




