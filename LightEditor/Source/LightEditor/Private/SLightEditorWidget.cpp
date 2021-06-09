#include "SLightEditorWidget.h"
#include "Runtime/Engine/Classes/Engine/Light.h"
#include "LightEditor.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SButton.h"

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/WeakObjectPtr.h"
#include "Runtime/Slate/Public/SlateBasics.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

//#define PLUGIN_NAME TEXT("LightEditor")
#define LOCTEXT_NAMESPACE "Synaptech"

SLightEditorWidget::SLightEditorWidget() {}
SLightEditorWidget::~SLightEditorWidget() {
    FEditorDelegates::OnDeleteActorsEnd.RemoveAll(this);
    FEditorDelegates::OnNewActorsDropped.RemoveAll(this);
    FEditorDelegates::OnEditCutActorsEnd.RemoveAll(this);
    FEditorDelegates::OnEditCopyActorsEnd.RemoveAll(this);
    FEditorDelegates::OnEditPasteActorsEnd.RemoveAll(this);
    FEditorDelegates::OnDuplicateActorsEnd.RemoveAll(this);
    FEditorDelegates::OnLightingBuildSucceeded.RemoveAll(this);
    
    FEditorDelegates::MapChange.RemoveAll(this);
    FEditorDelegates::OnMapOpened.RemoveAll(this);
    FEditorDelegates::NewCurrentLevel.RemoveAll(this);
    FWorldDelegates::LevelAddedToWorld.RemoveAll(this);
    FWorldDelegates::LevelRemovedFromWorld.RemoveAll(this);
    
}

void SLightEditorWidget::Construct(const FArguments& InArgs) {
    SAssignNew(GridPanel, SUniformGridPanel).MinDesiredSlotHeight(10).MinDesiredSlotWidth(80);
    SAssignNew(ScrollBox, SScrollBox).OnUserScrolled(this, &SLightEditorWidget::OnGridPanelScrolled);
    //
    ScrollBox->SetScrollBarRightClickDragAllowed(true);
    RebuildGridPanel();

    ScrollBox->AddSlot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
        .AutoHeight().Padding(0, 2, 0, 2)
        .VAlign(VAlign_Top).HAlign(HAlign_Fill)

        +SVerticalBox::Slot()
        .VAlign(VAlign_Fill).HAlign(HAlign_Fill)
        [
            GridPanel.ToSharedRef()
        ]
        ];
    //
    ChildSlot.HAlign(HAlign_Fill).VAlign(VAlign_Fill)[ScrollBox.ToSharedRef()];
    //
    //
    FEditorDelegates::OnDeleteActorsEnd.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    FEditorDelegates::OnEditCutActorsEnd.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    FEditorDelegates::OnEditCutActorsEnd.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    FEditorDelegates::OnEditCopyActorsEnd.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    FEditorDelegates::OnEditPasteActorsEnd.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    FEditorDelegates::OnDuplicateActorsEnd.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    FEditorDelegates::OnNewActorsDropped.AddRaw(this, &SLightEditorWidget::OnNewActorsDropped);
    FEditorDelegates::OnLightingBuildSucceeded.AddRaw(this, &SLightEditorWidget::RebuildGridPanel);
    //
    FEditorDelegates::MapChange.AddRaw(this, &SLightEditorWidget::OnMapChange);
    FEditorDelegates::OnMapOpened.AddRaw(this, &SLightEditorWidget::OnMapLoaded);
    FWorldDelegates::LevelAddedToWorld.AddRaw(this, &SLightEditorWidget::OnLevelAdded);
    FEditorDelegates::NewCurrentLevel.AddRaw(this, &SLightEditorWidget::OnNewCurrentLevel);
    FWorldDelegates::LevelRemovedFromWorld.AddRaw(this, &SLightEditorWidget::OnLevelRemoved);
}

bool SLightEditorWidget::IsInteractable() const {
    return IsEnabled();
}

bool SLightEditorWidget::SupportsKeyboardFocus() const {
    return true;
}


void SLightEditorWidget::OnGridPanelScrolled(float Offset) {}


void SLightEditorWidget::OnNewActorsDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors) {
    RebuildGridPanel();
}

void SLightEditorWidget::OnMapLoaded(const FString& Filename, bool AsTemplate) {
    RebuildGridPanel();
}

void SLightEditorWidget::OnMapChange(uint32 MapFlags) {
    RebuildGridPanel();
}

void SLightEditorWidget::OnNewCurrentLevel() {
    RebuildGridPanel();
}

void SLightEditorWidget::OnLevelAdded(ULevel* InLevel, UWorld* InWorld) {
    RebuildGridPanel();
}

void SLightEditorWidget::OnLevelRemoved(ULevel* InLevel, UWorld* InWorld) {
    RebuildGridPanel();
}


void SLightEditorWidget::RebuildGridPanel() {
    if (!GridPanel.IsValid()) { return; }
    //
    GridPanel->ClearChildren();
    {
        GridPanel->AddSlot(0, 0).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SNew(SBorder)
                .VAlign(VAlign_Center).HAlign(HAlign_Fill)
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
            [
                SNew(STextBlock)
                .Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
            .Text(FText::FromString(TEXT("Light")))
            .Justification(ETextJustify::Center)
            ]
            ];
        //
		GridPanel->AddSlot(1, 0).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SNew(SBorder)
                .VAlign(VAlign_Center).HAlign(HAlign_Fill)
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
            [
                SNew(STextBlock)
                .Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
            .Text(FText::FromString(TEXT("Color")))
            .Justification(ETextJustify::Center)
            ]
            ];
        //
        GridPanel->AddSlot(2, 0).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SNew(SBorder)
                .VAlign(VAlign_Center).HAlign(HAlign_Fill)
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
            [
                SNew(STextBlock)
                .Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
            .Text(FText::FromString(TEXT("Intensity")))
            .Justification(ETextJustify::Center)
            ]
            ];//
        GridPanel->AddSlot(3, 0).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SNew(SBorder)
                .VAlign(VAlign_Center).HAlign(HAlign_Fill)
                .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
                [
                SNew(STextBlock)
                .Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
                .Text(FText::FromString(TEXT("Rotation")))
                .Justification(ETextJustify::Center)
                ]
            ];
        GridPanel->AddSlot(4, 0).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SNew(SBorder)
                .VAlign(VAlign_Center).HAlign(HAlign_Fill)
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
            [
                SNew(STextBlock)
                .Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
            .Text(FText::FromString(TEXT("Cast Shadow")))
            .Justification(ETextJustify::Center)
            ]
            ];
            
        
    }
	TArray<ASkyLight*>Skies;
    TArray<ALight*>Lights;

    TArray<AActor*>BPActor;

	if (GEditor) {
		const FWorldContext &Context = GEditor->GetEditorWorldContext();
		UWorld* World = Context.World();
		//
		if (World) {
			for (TActorIterator<ALight>Actor(World); Actor; ++Actor) {
				if ((*Actor)->HasAnyFlags(RF_BeginDestroyed)) { continue; }
				{ Lights.Add(*Actor); }
			}
			for (TActorIterator<ASkyLight>Actor(World); Actor; ++Actor) {
				if ((*Actor)->HasAnyFlags(RF_BeginDestroyed)) { continue; }
			    { Skies.Add(*Actor); }
			}
            //bug, it gets all bpactor in world
            for (TActorIterator<AActor>Actor(World); Actor; ++Actor) {
                if ((*Actor)->HasAnyFlags(RF_BeginDestroyed)) { continue; }
                { BPActor.Add(*Actor); }
            }
		}
	}

	for (int32 I = 0; I < Skies.Num(); ++I) { SkyListItems.Add(TSharedPtr<SLE_List_Sky>(nullptr)); }
	for (int32 I = 0; I < Skies.Num(); ++I) { SkyColor.Add(TSharedPtr<SLE_Color_Sky>(nullptr)); }
	for (int32 I = 0; I < Skies.Num(); ++I) { SkyIntensity.Add(TSharedPtr<SLE_Intensity_Sky>(nullptr)); }

    for (int32 I = 0; I < Lights.Num(); ++I) { ListItems.Add(TSharedPtr<SLE_List>(nullptr)); }
    for (int32 I = 0; I < Lights.Num(); ++I) { ColorItems.Add(TSharedPtr<SLE_Color>(nullptr)); }
    for (int32 I = 0; I < Lights.Num(); ++I) { IntensityItems.Add(TSharedPtr<SLE_Intensity>(nullptr)); }
    for (int32 I = 0; I < Lights.Num(); ++I) { RotationItems.Add(TSharedPtr<SLE_Rotation>(nullptr)); }

	for (int32 I = 0; I < Skies.Num(); ++I) { SkyListItems.Add(TSharedPtr<SLE_List_Sky>(nullptr)); }
	for (int32 I = 0; I < Skies.Num(); ++I) { SkyColor.Add(TSharedPtr<SLE_Color_Sky>(nullptr)); }
	for (int32 I = 0; I < Skies.Num(); ++I) { SkyIntensity.Add(TSharedPtr<SLE_Intensity_Sky>(nullptr));}

    for (int32 I = 0; I < BPActor.Num(); ++I) { SkyListItems.Add(TSharedPtr<SLE_List_Sky>(nullptr)); }
    for (int32 I = 0; I < BPActor.Num(); ++I) { SkyColor.Add(TSharedPtr<SLE_Color_Sky>(nullptr)); }
    for (int32 I = 0; I < BPActor.Num(); ++I) { SkyIntensity.Add(TSharedPtr<SLE_Intensity_Sky>(nullptr)); }

    //CAST shadow
    for (int32 I = 0; I < Lights.Num(); ++I) { CastShadowItems.Add(TSharedPtr<SLE_CastShadow>(nullptr)); }

	for (int32 I = 0; I < Lights.Num(); ++I) {
		GridPanel->AddSlot(0, I + (Skies.Num() + 1)).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(ListItems[I], SLE_List, Lights[I])
			];
	}///
	//
	for (int32 I = 0; I < Lights.Num(); ++I) {
		GridPanel->AddSlot(1, I + (Skies.Num() + 1)).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(ColorItems[I], SLE_Color, Lights[I])
			];
	}///
	//
	for (int32 I = 0; I < Lights.Num(); ++I) {
		GridPanel->AddSlot(2, I + (Skies.Num() + 1)).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(IntensityItems[I], SLE_Intensity, Lights[I])
			];
	}///
	for (int32 I = 0; I < Skies.Num(); ++I) {
		GridPanel->AddSlot(0, I + 1).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(SkyListItems[I], SLE_List_Sky, Skies[I])
			];
	}///
	//
	for (int32 I = 0; I < Skies.Num(); ++I) {
		GridPanel->AddSlot(1, I + 1).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(SkyColor[I], SLE_Color_Sky, Skies[I])
			];
	}///
	//
	for (int32 I = 0; I < Skies.Num(); ++I) {
		GridPanel->AddSlot(2, I + 1).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(SkyIntensity[I], SLE_Intensity_Sky, Skies[I])
			];
	}
    for (int32 I = 0; I < Lights.Num(); ++I) {
        GridPanel->AddSlot(3, I + (Skies.Num() + 1)).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SAssignNew(RotationItems[I], SLE_Rotation, Lights[I])
            ];
    }///
    for (int32 I = 0; I < Lights.Num(); ++I) {
        GridPanel->AddSlot(4, I + (Skies.Num() + 1)).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
            [
                SAssignNew(CastShadowItems[I], SLE_CastShadow, Lights[I])
            ];
    }///

}

#undef LOCTEXT_NAMESPACE
