#include "LE_Color.h"

#include "Runtime/Core/Public/Misc/Attribute.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "Runtime/Engine/Classes/Components/LightComponent.h"

#define LOCTEXT_NAMESPACE "Synaptech"
#define PLUGIN_NAME TEXT("LightEditor")

//class ULightComponent;
//class UClass;

SLE_Color::SLE_Color() {}
SLE_Color::~SLE_Color() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLE_Color::Construct(const FArguments& InArgs, ALight* Target) {
	Item = Target;
	//
	//
	ChildSlot.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
	[
		SNew(SBox)
		.Padding(FMargin(4))
		[
			SNew(SBorder).Padding(FMargin(6))
			.VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		    .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
		    [
				SNew(SColorBlock)
				.OnMouseButtonDown(this, &SLE_Color::OnClickedItem)
				.Color(this, &SLE_Color::GetColor)
				.IgnoreAlpha(false)
			]
		]
	];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FLinearColor SLE_Color::GetColor() const {
	if (!Item.IsValid()) { return FLinearColor::Black; }
	//
	return Item->GetLightColor();
}

void SLE_Color::SetColor(FLinearColor NewColor) {
	if (!Item.IsValid()) { return; }
	//
	FPropertyChangedEvent PropEditEvent(ULightComponent::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(ULightComponent, LightColor)));
	EComponentMobility::Type Mobility = Item->GetLightComponent()->Mobility;
	//
	Item->Modify();
	Item->GetLightComponent()->Mobility = EComponentMobility::Stationary;
	Item->GetLightComponent()->InvalidateLightingCache();
	Item->GetLightComponent()->SetLightColor(NewColor);
	Item->GetLightComponent()->MarkRenderStateDirty();
	//
	Item->GetLightComponent()->PostEditChangeProperty(PropEditEvent);
	Item->GetLightComponent()->Mobility = Mobility;
}


void SLE_Color::OnInteractivePickEnd() {}
void SLE_Color::OnInteractivePickBegin() {}
void SLE_Color::OnColorPickerClosed(const TSharedRef<SWindow>& Window) {}

void SLE_Color::OnColorPickerCancelled(FLinearColor OriginalColor) {
	if (!Item.IsValid()) { return; }
	//
	Item->SetLightColor(OriginalColor);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FReply SLE_Color::OnClickedItem(const FGeometry& Geometry, const FPointerEvent& MouseEvent) {
	if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
	if (!Item.IsValid()) { return FReply::Unhandled(); }
	//
	FColorPickerArgs PickerArgs; {
		PickerArgs.bUseAlpha = true;
		PickerArgs.bOnlyRefreshOnOk = false;
		PickerArgs.bOnlyRefreshOnMouseUp = false;
		PickerArgs.DisplayGamma = TAttribute<float>::Create(TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
		PickerArgs.OnColorPickerCancelled = FOnColorPickerCancelled::CreateSP(this, &SLE_Color::OnColorPickerCancelled);
		PickerArgs.OnInteractivePickBegin = FSimpleDelegate::CreateSP(this, &SLE_Color::OnInteractivePickBegin);
		PickerArgs.OnColorPickerWindowClosed = FOnWindowClosed::CreateSP(this, &SLE_Color::OnColorPickerClosed);
		PickerArgs.OnInteractivePickEnd = FSimpleDelegate::CreateSP(this, &SLE_Color::OnInteractivePickEnd);
		PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &SLE_Color::SetColor);
		PickerArgs.InitialColorOverride = Item->GetLightColor();
		PickerArgs.ParentWidget = ColorBlock;
	} OpenColorPicker(PickerArgs);
	//
	return FReply::Handled();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SLE_Color::IsInteractable() const {
	return IsEnabled();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
