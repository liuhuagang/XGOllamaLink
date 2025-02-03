// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "XGOllamaVersionRespType.generated.h"


USTRUCT(BlueprintType)
struct XGOLLAMALINK_API FXGOllamaVersionRespInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGOllama")
	FString	version = TEXT("");
};


