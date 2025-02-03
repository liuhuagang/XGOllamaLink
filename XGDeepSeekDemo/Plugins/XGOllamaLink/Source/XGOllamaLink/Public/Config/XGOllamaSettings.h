// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "XGOllamaSettings.generated.h"

/**
 * XGOllamaSettings
 * some Ollama settings,just to show you how to call on it
 * 
 */
UCLASS(Config = XGOllamaSettings, defaultconfig)
class XGOLLAMALINK_API UXGOllamaSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UXGOllamaSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGOllamaSettings();

	virtual FName GetContainerName() const override;

	virtual FName GetCategoryName() const override;

	virtual FName GetSectionName() const override;

public:

	static UXGOllamaSettings* GetXGOllamaSettings();


public:

	//Current Plugin Version
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGOllamaInfo")
	FString PluginVersion = TEXT("");

	//deepseek-r1 download url
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGOllamaInfo")
	FString DeepSeekURL =TEXT("");

	//Ollama API URL
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGOllamaInfo")
	FString OllamaAPIURL = TEXT("");

};
