
#include "LE_List.h"
#include "LightEditorStyle.h"

#include "Engine/SpotLight.h"
#include "Engine/RectLight.h"
#include "Engine/PointLight.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"

#define LOCTEXT_NAMESPACE "Synaptech"

SLE_List::SLE_List() {}
SLE_List::~SLE_List() {}


void SLE_List::Construct(const FArguments& InArgs, ALight* Target) {
	TSharedRef<SButton>Button = SNew(SButton);
	FText Caption = FText::FromString(TEXT(""));
	
	Item = Target;
	if (Item.IsValid()) { Caption = FText::FromString(Item->GetActorLabel()); }
	
	SAssignNew(Button, SButton)
		.ButtonStyle(FEditorStyle::Get(), "FlatButton.Default")
		.ForegroundColor(FSlateColor::UseForeground())
		.OnClicked(this, &SLE_List::OnClickedItem)
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SImage)
			.Image(this, &SLE_List::GetTypeBrush)
		.ToolTipText(this, &SLE_List::GetTypeTooltip)
		]
	+ SHorizontalBox::Slot().Padding(2)
		.HAlign(HAlign_Fill).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Margin(FMargin(2))
			.Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
		.Justification(ETextJustify::Center)
		.Text(Caption)
		]
		];

	ChildSlot
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBox).Padding(FMargin(4))
			[
				Button
			]
		];
}


FReply SLE_List::OnClickedItem() {
	if (GEditor && Item.IsValid()) {
		GEditor->SelectNone(true, true, true);
		GEditor->SelectActor(Item.Get(), true, true, true, true);
		
		TArray<AActor*>Actors; Actors.Add(Item.Get());
		GEditor->MoveViewportCamerasToActor(Actors, true);
	}
	return FReply::Handled();
}

FText SLE_List::GetTypeTooltip() const {
	if (!Item.IsValid()) { return FText::FromString(TEXT("Light Source")); }
	
	if (Item.Get()->IsA(ASpotLight::StaticClass())) { return FText::FromString(TEXT("Spot Light")); }
	if (Item.Get()->IsA(ARectLight::StaticClass())) { return FText::FromString(TEXT("Rect Light")); }
	if (Item.Get()->IsA(APointLight::StaticClass())) { return FText::FromString(TEXT("Point Light")); }
	if (Item.Get()->IsA(ADirectionalLight::StaticClass())) { return FText::FromString(TEXT("Directional Light")); }
	
	return FText::FromString(TEXT("Light Source"));
}

const FSlateBrush* SLE_List::GetTypeBrush() const {
	const FSlateBrush* Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Point"));
	if (!Item.IsValid()) { return Brush; }
	
	EComponentMobility::Type Mobil = Item.Get()->GetLightComponent()->Mobility;
	switch (Mobil) {
	case EComponentMobility::Static:
	{
		if (Item.Get()->IsA(ASpotLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Spot")); }
		if (Item.Get()->IsA(ARectLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Rect")); }
		if (Item.Get()->IsA(APointLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.PointStatic")); }
		if (Item.Get()->IsA(ADirectionalLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Directional")); }
	} break;
	
	case EComponentMobility::Stationary:
	{
		if (Item.Get()->IsA(ASpotLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Spot")); }
		if (Item.Get()->IsA(ARectLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Rect")); }
		if (Item.Get()->IsA(APointLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Point")); }
		if (Item.Get()->IsA(ADirectionalLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.Directional")); }
	} break;
	
	case EComponentMobility::Movable:
	{
		if (Item.Get()->IsA(ASpotLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.SpotMove")); }
		if (Item.Get()->IsA(ARectLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.RectMove")); }
		if (Item.Get()->IsA(APointLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.PointMove")); }
		if (Item.Get()->IsA(ADirectionalLight::StaticClass())) { Brush = FLightEditorStyle::Get()->GetBrush(TEXT("LE.DirectionalMove")); }
	} break;
	default: break;
	}
	
	return Brush;
}

bool SLE_List::IsInteractable() const {
	return IsEnabled();
}


#undef LOCTEXT_NAMESPACE
