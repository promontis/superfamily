// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#include "Superfamily.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogSuperfamily);

void FSuperfamilyModule::StartupModule()
{
	UE_LOG(LogSuperfamily, Log, TEXT("Superfamily module starting up"));
}

void FSuperfamilyModule::ShutdownModule()
{
	UE_LOG(LogSuperfamily, Log, TEXT("Superfamily module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FSuperfamilyModule, Superfamily, "Superfamily");
