// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightEditorStyle.h"
#include "LightEditor.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

#define PLUGIN_BRUSH(RelativePath,...) FSlateImageBrush(FLightEditorStyle::InContent(RelativePath,".png"),__VA_ARGS__)

TSharedPtr<FSlateStyleSet> FLightEditorStyle::StyleSet = nullptr;
TSharedPtr<ISlateStyle> FLightEditorStyle::Get() { return StyleSet; }


FString FLightEditorStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension) {
	static FString Content = IPluginManager::Get().FindPlugin(PLUGIN_NAME)->GetContentDir();
	return (Content / RelativePath) + Extension;
}

FName FLightEditorStyle::GetStyleSetName() {
	static FName StyleName(TEXT("LightEditorStyle"));
	return StyleName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FLightEditorStyle::Initialize() {
	if (StyleSet.IsValid()) { return; }
	//
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon128x128(128.0f, 128.0f);
	//
	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->Set("LightEditor.Icon", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon16x16));
	StyleSet->Set("LightEditor.LightEditorTab", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon40x40));
	StyleSet->Set("LightEditor.LightEditorTab.Small", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon20x20));

	StyleSet->Set("LE.Sky", new PLUGIN_BRUSH(TEXT("Icons/Sky"), Icon40x40));
	StyleSet->Set("LE.Spot", new PLUGIN_BRUSH(TEXT("Icons/SpotLight_64x"), Icon40x40));
	StyleSet->Set("LE.Point", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon40x40));
	StyleSet->Set("LE.SpotMove", new PLUGIN_BRUSH(TEXT("Icons/SpotLight_64x"), Icon40x40));
	StyleSet->Set("LE.PointMove", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon40x40));
	StyleSet->Set("LE.PointStatic", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon40x40));
	StyleSet->Set("LE.Directional", new PLUGIN_BRUSH(TEXT("Icons/DirectionalLight_64x"), Icon40x40));
	StyleSet->Set("LE.DirectionalMove", new PLUGIN_BRUSH(TEXT("Icons/DirectionalLight_64x"), Icon40x40));
	//
	StyleSet->Set("LE.Rect", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon40x40));
	StyleSet->Set("LE.RectMove", new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"), Icon40x40));
	//
	StyleSet->Set("LE.Solo",new PLUGIN_BRUSH(TEXT("Icons/PointLight_64x"),Icon20x20));
	
	//
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

void FLightEditorStyle::Shutdown() {
	if (StyleSet.IsValid()) {
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}///
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef PLUGIN_BRUSH
