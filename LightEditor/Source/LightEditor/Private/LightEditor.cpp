
#include "LightEditor.h"
#include "LightEditorStyle.h"
#include "LightEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/SBoxPanel.h"
#include "ToolMenus.h"
#include "SLightEditorWidget.h"

#include "LightEditor.h"
#include "LevelEditor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOCTEXT_NAMESPACE "Synaptech"



void FLightEditor::StartupModule() {
	FLightEditorStyle::Initialize();
	FLightEditorCommands::Register();
	//
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TAB, FOnSpawnTab::CreateRaw(this, &FLightEditor::OnSpawnLightEditorTab))
		.SetDisplayName(LOCTEXT("LightEditorTab_Title", "Light Editor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	//
	Commands = MakeShareable(new FUICommandList);
	Commands->MapAction(FLightEditorCommands::Get().LightEditorTab, FExecuteAction::CreateRaw(this, &FLightEditor::OnToolbarButtonClicked), FCanExecuteAction());
	//
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender>ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, Commands, FToolBarExtensionDelegate::CreateRaw(this, &FLightEditor::AddToolBarButton));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	//
	//
	LE_Extender = MakeShareable(new FExtender());
	LE_Extender->AddMenuExtension("General", EExtensionHook::After, TSharedPtr<FUICommandList>(), FMenuExtensionDelegate::CreateStatic(&FLightEditor::ExtendMenu));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(LE_Extender);
}

void FLightEditor::ShutdownModule() {
	FLightEditorCommands::Unregister();
	FLightEditorStyle::Shutdown();
	//
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TAB);
}



TSharedRef<SDockTab>FLightEditor::OnSpawnLightEditorTab(const FSpawnTabArgs& SpawnTabArgs) {
	TSharedRef<SDockTab>LEAB = SNew(SDockTab).TabRole(ETabRole::NomadTab);
	//
	LEAB->SetTabIcon(FLightEditorStyle::Get()->GetBrush(TEXT("LightEditor.Icon")));
	LEAB->SetContent(SNew(SLightEditorWidget));
	//
	return LEAB;
}

//void FLightEditor::InvokeTab() {
	//TSharedRef<SDockTab>LEAB = FGlobalTabmanager::Get()->InvokeTab(TAB);
//}

void FLightEditor::OnToolbarButtonClicked() {
	FLightEditor::InvokeTab();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void FLightEditorCommands::RegisterCommands() {
	UI_COMMAND(LightEditorTab, "Light Editor", "Light Editor Tool", EUserInterfaceActionType::Button, FInputGesture());
}*/

/*void FLightEditor::AddToolBarButton(FToolBarBuilder& Builder) {
	Builder.AddToolBarButton(FLightEditorCommands::Get().LightEditorTab);
}*/

void FLightEditor::ExtendMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("LE_InvokeTab", "Light Editor..."),
		LOCTEXT("LE_InvokeTab_Tooltip", "Light Editor tool"),
		FSlateIcon(FLightEditorStyle::Get().Get()->GetStyleSetName(), "LightEditor.LightEditorTab"),
		FUIAction(FExecuteAction::CreateStatic(&FLightEditor::InvokeTab))
	);///
}

void FLightEditor::InvokeTab()
{
	TSharedRef<SDockTab>LEAB = FGlobalTabmanager::Get()->InvokeTab(TAB);
}



#undef LOCTEXT_NAMESPACE



IMPLEMENT_MODULE(FLightEditor, LightEditor);
