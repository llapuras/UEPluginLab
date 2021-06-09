// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MaterialLibraryStyle.h"

class FMaterialLibraryCommands : public TCommands<FMaterialLibraryCommands>
{
public:

	FMaterialLibraryCommands()
		: TCommands<FMaterialLibraryCommands>(TEXT("MaterialLibrary"), NSLOCTEXT("Contexts", "MaterialLibrary", "MaterialLibrary Plugin"), NAME_None, FMaterialLibraryStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};