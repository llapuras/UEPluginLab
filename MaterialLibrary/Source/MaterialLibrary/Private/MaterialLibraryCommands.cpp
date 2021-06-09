// Copyright Epic Games, Inc. All Rights Reserved.

#include "MaterialLibraryCommands.h"

#define LOCTEXT_NAMESPACE "FMaterialLibraryModule"

void FMaterialLibraryCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MaterialLibrary", "Bring up MaterialLibrary window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
