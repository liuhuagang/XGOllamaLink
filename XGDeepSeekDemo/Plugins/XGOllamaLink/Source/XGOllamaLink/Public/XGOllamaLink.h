// Copyright 2025 Xiao Gang. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FXGOllamaLinkModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
