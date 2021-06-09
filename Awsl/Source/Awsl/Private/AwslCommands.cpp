// Copyright Epic Games, Inc. All Rights Reserved.

#include "AwslCommands.h"

#define LOCTEXT_NAMESPACE "FAwslModule"

void FAwslCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Awsl", "Bring up Awsl window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
