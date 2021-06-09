// Copyright Epic Games, Inc. All Rights Reserved.

#include "Awsl.h"
#include "AwslStyle.h"
#include "AwslCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "Sequencer/Public/ISequencer.h"
#include "Sequencer/Public/ISequencerModule.h"
#include "../Plugins/MovieScene/ActorSequence/Source/ActorSequence/Public/ActorSequence.h"
#include "../Plugins/MovieScene/ActorSequence/Source/ActorSequence/Public/ActorSequenceComponent.h"

static const FName AwslTabName("AwslTab01");
static const FName AwslTab02Name("AwslTab02");

#define LOCTEXT_NAMESPACE "FAwslModule"

void FAwslModule::StartupModule()
{

	FSequencerInitParams SequencerInitParams;
	{
		FSequencerInitParams();
	}

	ISequencerModule& seq = FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer"); // .CreateSequencer(SequencerInitParams);
	//TSharedRef<ISequencer>  Sequencer = seq.CreateSequencer(SequencerInitParams);

	//-------------------------------------------------------------

	FAwslStyle::Initialize();
	FAwslStyle::ReloadTextures();

	FAwslCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	//�������ťӳ�䵽PluginButtonClicked�����ϣ��������������ỽ���������������tab
	PluginCommands->MapAction(
		FAwslCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAwslModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAwslModule::RegisterMenus));

	//��ȡtab����Ȼ��֮ǰ���趨��OnSpawnPluginTabע��������tab
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AwslTabName, 
		FOnSpawnTab::CreateRaw(this, &FAwslModule::OnSpawnPluginTab01))
		.SetDisplayName(LOCTEXT("FAwslTabTitle", "Awsl01"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AwslTab02Name, 	
		FOnSpawnTab::CreateRaw(this, &FAwslModule::OnSpawnPluginTab02))
		.SetDisplayName(LOCTEXT("FAwslTabTitle", "Awsl02"))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
	
	
	//����������Լ��������
}

void FAwslModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAwslStyle::Shutdown();

	FAwslCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AwslTabName);
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AwslTab02Name);
	}
}

TSharedRef<SDockTab> FAwslModule::OnSpawnPluginTab01(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FAwslModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Awsl.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

TSharedRef<SDockTab> FAwslModule::OnSpawnPluginTab02(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<class SDockTab> DOCK = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
			/*SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GenerateSeq", "Generate Seq"))
			]*/
			SAssignNew(SeqContent, SBox)
			.MinDesiredHeight(200)

		]
		];

	SeqContent->SetContent(SNew(STextBlock).Text(LOCTEXT("NothingSelected", "Select a sequence")));
	//SeqContent->SetContent(Sequencer->GetSequencerWidget());

	return DOCK;
}


void FAwslModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AwslTabName); 
	{
		FGlobalTabmanager::Get()->TryInvokeTab(AwslTab02Name);
	}
}


//ע������ť���ֵ�λ�ã�����������ע���ڹؿ��༭����
void FAwslModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAwslCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAwslCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAwslModule, Awsl)