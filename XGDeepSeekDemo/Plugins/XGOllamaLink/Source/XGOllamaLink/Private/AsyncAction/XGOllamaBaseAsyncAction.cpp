// Copyright 2025 Xiao Gang. All Rights Reserved.

#include "XGOllamaBaseAsyncAction.h"

#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"

UXGOllamaBaseAsyncAction::UXGOllamaBaseAsyncAction(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	AsyncID(FGuid::NewGuid())
{


}

void UXGOllamaBaseAsyncAction::Activate()
{
	Super::Activate();

	AsyncTask(ENamedThreads::GameThread, [this]() {

		this->Activate_Internal();

		});

}

void UXGOllamaBaseAsyncAction::Activate_Internal()
{


}
