// Copyright 2025 Huagang Liu. All Rights Reserved.

#include "XGOllamaSettings.h"
#include "Interfaces/IPluginManager.h"
#include "PluginDescriptor.h"

UXGOllamaSettings::UXGOllamaSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	IPluginManager& PluginManager = IPluginManager::Get();

	TSharedPtr<IPlugin> PluginPtr = PluginManager.FindPlugin(TEXT("XGOllamaLink"));

	if (PluginPtr.IsValid())
	{
		FPluginDescriptor PluginDescriptor = PluginPtr->GetDescriptor();
		PluginVersion = PluginDescriptor.VersionName;
	}


	DeepSeekURL = TEXT("https://ollama.com/library/deepseek-r1");

	OllamaAPIURL = TEXT("https://github.com/ollama/ollama/blob/main/docs/api.md");


}

UXGOllamaSettings::~UXGOllamaSettings()
{

}

FName UXGOllamaSettings::GetContainerName() const
{
	return TEXT("Project");
}

FName UXGOllamaSettings::GetCategoryName() const
{
	return TEXT("XGPlugins");
}

FName UXGOllamaSettings::GetSectionName() const
{
	return TEXT("XGOllamaSettings");
}

UXGOllamaSettings* UXGOllamaSettings::GetXGOllamaSettings()
{
	UXGOllamaSettings* Settings = GetMutableDefault<UXGOllamaSettings>();

	return Settings;
}
