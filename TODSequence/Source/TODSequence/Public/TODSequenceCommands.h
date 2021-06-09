// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TODSequenceStyle.h"

class FTODSequenceCommands : public TCommands<FTODSequenceCommands>
{
public:

	FTODSequenceCommands()
		: TCommands<FTODSequenceCommands>(TEXT("TODSequence"), NSLOCTEXT("Contexts", "TODSequence", "TODSequence Plugin"), NAME_None, FTODSequenceStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};