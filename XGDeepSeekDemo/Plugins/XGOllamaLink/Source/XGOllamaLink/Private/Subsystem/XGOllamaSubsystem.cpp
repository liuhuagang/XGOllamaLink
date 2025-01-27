// Copyright 2025 Xiao Gang. All Rights Reserved.

#include "XGOllamaSubsystem.h"

bool UXGOllamaLinkSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    return true;
}

void UXGOllamaLinkSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UXGOllamaLinkSubsystem::Deinitialize()
{
    Super::Deinitialize();
}
