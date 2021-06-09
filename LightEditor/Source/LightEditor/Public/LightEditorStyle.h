// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**  */
class FLightEditorStyle
{
public:

	static void Initialize();

	static void Shutdown();


	static void ReloadTextures();

	
	//static const ISlateStyle& Get();

	static FName GetStyleSetName();

	
	
	//static void Initialize();
	//static void Shutdown();
	//static FName GetStyleSetName();
	static TSharedPtr<ISlateStyle> Get();
	
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
	static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);


	static TSharedPtr< class FSlateStyleSet > StyleInstance;
	static TSharedRef< class FSlateStyleSet > Create();
};