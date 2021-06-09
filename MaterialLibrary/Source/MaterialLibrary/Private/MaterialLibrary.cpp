// Copyright Epic Games, Inc. All Rights Reserved.

#include "MaterialLibrary.h"
#include "MaterialLibraryStyle.h"
#include "MaterialLibraryCommands.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Framework/Docking/TabManager.h"
#include <../Private/ContentBrowserSingleton.h>
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include <Widgets/Layout/SBorder.h>
#include <ContentBrowserDelegates.h>

static const FName MaterialLibraryTabName("MaterialLibrary");
static const FName InnerTabName2("Settings");
static const FName InnerTabName("Material Lab");

#define LOCTEXT_NAMESPACE "FMaterialLibraryModule"

void FMaterialLibraryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FMaterialLibraryStyle::Initialize();
	FMaterialLibraryStyle::ReloadTextures();

	FMaterialLibraryCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMaterialLibraryCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMaterialLibraryModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMaterialLibraryModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MaterialLibraryTabName, FOnSpawnTab::CreateRaw(this, &FMaterialLibraryModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMaterialLibraryTabTitle", "MaterialLibrary"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
   
}

void FMaterialLibraryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMaterialLibraryStyle::Shutdown();

	FMaterialLibraryCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MaterialLibraryTabName);
}

TSharedRef<SDockTab> FMaterialLibraryModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	const TSharedRef<SDockTab> NomadTab = SNew(SDockTab).TabRole(ETabRole::NomadTab);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SAssignNew(ContentSlate, SContentSlate)
		];
}

void FMaterialLibraryModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MaterialLibraryTabName);
}


void FMaterialLibraryModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMaterialLibraryCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMaterialLibraryCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMaterialLibraryModule, MaterialLibrary)