// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "XGOllamaBaseAsyncAction.generated.h"

UCLASS()
class XGOLLAMALINK_API UXGOllamaBaseAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


public:

	UXGOllamaBaseAsyncAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Activate() override;

protected:

	virtual void Activate_Internal();

public:

	FGuid AsyncID;
};
