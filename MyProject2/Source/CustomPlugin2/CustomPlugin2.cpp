// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

// USE THIS IF DEVELOPING A PLUGIN
/*#include "CustomPlugin2.h"

#define LOCTEXT_NAMESPACE "FCustomPlugin2Module"

void FCustomPlugin2Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCustomPlugin2Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomPlugin2Module, CustomPlugin2)*/

// USE THIS IF DEVELOPING A GAME MODULE

#include "CustomPlugin2.h"

IMPLEMENT_PRIMARY_GAME_MODULE(CustomPlugin2, "CustomPlugin2");