// Copyright Epic Games, Inc. All Rights Reserved.

#include "TODSequenceCommands.h"

#define LOCTEXT_NAMESPACE "FTODSequenceModule"

void FTODSequenceCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TODSequence", "Bring up TODSequence window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
