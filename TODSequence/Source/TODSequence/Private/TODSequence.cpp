// Copyright Epic Games, Inc. All Rights Reserved.

#include "TODSequence.h"
#include "TODSequenceAsset.h"
#include "TODSequenceStyle.h"
#include "TODSequenceCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "AssetToolsModule.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "LevelSequence.h"
#include "EngineUtils.h"
#include "Engine/World.h"

static const FName TODSequenceTabName("TODSequence");

#define LOCTEXT_NAMESPACE "FTODSequenceModule"

void FTODSequenceModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTODSequenceStyle::Initialize();
	FTODSequenceStyle::ReloadTextures();

	FTODSequenceCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTODSequenceCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTODSequenceModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTODSequenceModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TODSequenceTabName, FOnSpawnTab::CreateRaw(this, &FTODSequenceModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTODSequenceTabTitle", "TODSequence"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTODSequenceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTODSequenceStyle::Shutdown();

	FTODSequenceCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TODSequenceTabName);
}

TSharedRef<SDockTab> FTODSequenceModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTODSequenceModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TODSequence.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Text(LOCTEXT("GenerateSeq", "Generate Seq"))
				.OnClicked_Raw(this, &FTODSequenceModule::CreateTODSequence)			
			]
		];
}

//---------------------------------
//craete new level sequencer asset
//---------------------------------
FReply FTODSequenceModule::CreateTODSequence()
{

	UWorld* World;

	if (GEditor) {
		const FWorldContext& Context = GEditor->GetEditorWorldContext();
		World = Context.World();
		FString NewPath = World->GetMapName();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *NewPath);
	}

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();


	FString AssetName = "LS_awsl";
	FString NewPath = "/Game/";

	//21.6.7
	//TODO: CHECK if exist before excuting following code

	if (NewAsset) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Existed"));	
	}
	else 
	{
		for (TObjectIterator<UClass> It; It; ++It)
		{
			UClass* CurrentClass = *It;
			if (CurrentClass->IsChildOf(UFactory::StaticClass()) && !(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
			{
				UFactory* Factory = Cast<UFactory>(CurrentClass->GetDefaultObject());
				if (Factory->CanCreateNew() && Factory->ImportPriority >= 0 && Factory->SupportedClass == ULevelSequence::StaticClass())
				{
					NewAsset = AssetTools.CreateAsset(AssetName, NewPath, ULevelSequence::StaticClass(), Factory);
					UE_LOG(LogTemp, Warning, TEXT("Created?"));
				}
			}
		}
	}





	return FReply::Handled();
}

void FTODSequenceModule::PluginButtonClicked()
{	
	FGlobalTabmanager::Get()->TryInvokeTab(TODSequenceTabName);
}

void FTODSequenceModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTODSequenceCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTODSequenceCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTODSequenceModule, TODSequence)