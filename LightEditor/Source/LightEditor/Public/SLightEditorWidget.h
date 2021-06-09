#pragma once

#include "LightEditorStyle.h"
#include "CoreMinimal.h"
#include "Widgets/SUserWidget.h"

#include "LE_List.h"
#include "LE_Color.h"
#include "LE_Intensity.h"
#include "LE_Rotation.h"
#include "LE_Color_Sky.h"
#include "LE_Intensity_Sky.h"
#include "LE_List_Sky.h"
#include "LE_CastShadow.h"

#include "Runtime/Slate/Public/Widgets/Layout/SBox.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SSearchBox.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScrollBox.h"
#include "Runtime/SlateCore/Public/Widgets/Images/SImage.h"
#include "Runtime/Slate/Public/Widgets/Input/SNumericEntryBox.h"
#include "Runtime/Slate/Public/Widgets/Layout/SUniformGridPanel.h"

#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

#include "Editor/EditorEngine.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"
//

class SLightEditorWidget : public SCompoundWidget
{
private:
	TSharedPtr<SScrollBox>ScrollBox;
	TSharedPtr<SUniformGridPanel>GridPanel;
	TArray<TSharedPtr<SLE_List>>ListItems;
	TArray<TSharedPtr<class SLE_Color>>ColorItems;
	TArray<TSharedPtr<SLE_Intensity>>IntensityItems;
	TArray<TSharedPtr<SLE_Rotation>>RotationItems;
	TArray<TSharedPtr<SLE_List_Sky>>SkyListItems;
	TArray<TSharedPtr<SLE_Color_Sky>>SkyColor;
	TArray<TSharedPtr<SLE_Intensity_Sky>>SkyIntensity;
	TArray<TSharedPtr<class SLE_CastShadow>>CastShadowItems;
	
public:
	SLightEditorWidget();
	virtual ~SLightEditorWidget() override;
	SLATE_USER_ARGS(SLightEditorWidget)
	{}
	SLATE_END_ARGS()

		// MUST Provide this function for SNew to call!
	void Construct(const FArguments& InArgs);
	virtual bool IsInteractable() const override;
	virtual bool SupportsKeyboardFocus() const override;

	void RebuildGridPanel();
	//
	void OnGridPanelScrolled(float Offset);
	void OnNewActorsDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors);

	void OnNewCurrentLevel();
	void OnMapChange(uint32 MapFlags);
	void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);
	void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);
	void OnMapLoaded(const FString& Filename, bool AsTemplate);

};
