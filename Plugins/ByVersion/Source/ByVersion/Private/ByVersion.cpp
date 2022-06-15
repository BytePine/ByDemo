// Copyright Epic Games, Inc. All Rights Reserved.

#include "ByVersion.h"

#define LOCTEXT_NAMESPACE "FByVersionModule"

void FByVersionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FByVersionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FByVersionModule, ByVersion)