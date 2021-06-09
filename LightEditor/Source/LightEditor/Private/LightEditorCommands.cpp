// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightEditorCommands.h"

#define LOCTEXT_NAMESPACE "FLightEditorModule"
/*
void FLightEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "LightEditor", "Bring up LightEditor window", EUserInterfaceActionType::Button, FInputGesture());
}
*/

void FLightEditorCommands::RegisterCommands() {
	UI_COMMAND(LightEditorTab, "Light Editor", "Light Editor Tool", EUserInterfaceActionType::Button, FInputGesture());
}

void FLightEditor::AddToolBarButton(FToolBarBuilder& Builder) {
	Builder.AddToolBarButton(FLightEditorCommands::Get().LightEditorTab);
}




#undef LOCTEXT_NAMESPACE
