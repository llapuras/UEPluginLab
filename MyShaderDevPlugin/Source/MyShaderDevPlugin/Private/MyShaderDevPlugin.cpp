// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyShaderDevPlugin.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FMyShaderDevPluginModule"

void FMyShaderDevPluginModule::StartupModule()
{
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
}

void FMyShaderDevPluginModule::ShutdownModule()
{
	// Cleanup the virtual source directory mapping.
	ResetAllShaderSourceDirectoryMappings();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_PRIMARY_GAME_MODULE(FMyShaderDevPluginModule, MyShaderDevPlugin,"MyShaderDevPlugin")