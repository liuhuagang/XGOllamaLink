// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "XGOllamaSubsystem.generated.h"

UCLASS()
class XGOLLAMALINK_API UXGOllamaLinkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;




};
