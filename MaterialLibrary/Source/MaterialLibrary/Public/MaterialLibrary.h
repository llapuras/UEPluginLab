// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "../Private/ContentBrowserSingleton.h"
#include "Framework/Docking/TabManager.h"
#include "ContentBrowserModule.h"
#include "ContentSlate.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMaterialLibraryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	//TArray<FAssetData> AssetDatas;

private:

	void RegisterMenus();
	//void LoadContentLib();
	TSharedPtr<class SContentSlate> ContentSlate;
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<class FTabManager> TabManager;
	TSharedPtr<FTabManager::FLayout> TabManagerLayout;

	FName ContentBrowserTabIDs[MAX_CONTENT_BROWSERS];
	//TArray<FAssetData> AssetDatas;
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
