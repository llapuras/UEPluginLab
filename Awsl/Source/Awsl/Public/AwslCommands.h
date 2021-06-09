// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AwslStyle.h"

class FAwslCommands : public TCommands<FAwslCommands>
{
public:

	FAwslCommands()
		: TCommands<FAwslCommands>(TEXT("Awsl"), NSLOCTEXT("Contexts", "Awsl", "Awsl Plugin"), NAME_None, FAwslStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};