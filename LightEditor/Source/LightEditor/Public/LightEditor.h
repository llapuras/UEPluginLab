// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Engine/Classes/Engine/Light.h"
//
#include "LightEditor.h"
#include "SLightEditorWidget.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/MultiBox/MultiBoxExtender.h"

#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/Slate/Public/Widgets/Docking/SDockTab.h"
#include "UObject/Object.h"
#include "UObject/WeakObjectPtr.h"
#include "Runtime/Slate/Public/SlateBasics.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "Runtime/Engine/Classes/Engine/SkyLight.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"

#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Editor/ContentBrowser/Public/IContentBrowserSingleton.h"


#include "LightEditorStyle.h"

#define PLUGIN_NAME TEXT("LightEditor")

class ILightEditor : public IModuleInterface {
public:
	static inline ILightEditor& Get() {
		return FModuleManager::LoadModuleChecked<ILightEditor>("LightEditor");
	}///
	//
	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("LightEditor");
	}///
};
#define LOCTEXT_NAMESPACE "Synaptech"


static const FName TAB("TAB_LightEditor");

class FLightEditor : public ILightEditor {
private:
	TSharedPtr<FExtender>LE_Extender;
	TSharedPtr<FUICommandList>Commands;
	//
	TSharedRef<SDockTab>OnSpawnLightEditorTab(const FSpawnTabArgs& SpawnTabArgs);
	//
	void AddToolBarButton(FToolBarBuilder& Builder);


public:
	static void ExtendMenu(FMenuBuilder& MenuBuilder);
	static void InvokeTab();
	//
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//
	void OnToolbarButtonClicked();
};

#undef LOCTEXT_NAMESPACE
