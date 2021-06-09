
#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LightEditorStyle.h"

class FLightEditorCommands : public TCommands<FLightEditorCommands> {

public:
	TSharedPtr<FUICommandInfo>LightEditorTab;

	FLightEditorCommands() :TCommands<FLightEditorCommands>(TEXT("LightEditor"), NSLOCTEXT("Contexts", "LightEditor", "Light Editor"), NAME_None, FLightEditorStyle::GetStyleSetName()) {}
	//
	virtual void RegisterCommands() override;
};

#undef LOCTEXT_NAMESPACE