// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

#include "EvaTTSPlugin.h"

#define LOCTEXT_NAMESPACE "FEvaTTSPluginModule"

void FEvaTTSPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FEvaTTSPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEvaTTSPluginModule, EvaTTSPlugin)