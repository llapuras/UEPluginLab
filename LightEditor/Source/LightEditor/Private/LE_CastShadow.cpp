#include "LE_CastShadow.h"

#include "Runtime/Core/Public/Misc/Attribute.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "Runtime/Engine/Classes/Components/LightComponent.h"

#define LOCTEXT_NAMESPACE "Synaptech"
#define PLUGIN_NAME TEXT("LightEditor")

//class ULightComponent;
//class UClass;

SLE_CastShadow::SLE_CastShadow() {}
SLE_CastShadow::~SLE_CastShadow() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLE_CastShadow::Construct(const FArguments& InArgs, ALight* Target) {
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
			/*SNew(SColorBlock)
			.OnMouseButtonDown(this, &SLE_CastShadow::OnClickedItem)
			.Color(this, &SLE_CastShadow::GetColor)
			.IgnoreAlpha(false)*/
			SNew(SCheckBox)
			.IsChecked(this, &SLE_CastShadow::EnableCastShadow)
			.OnCheckStateChanged(this, &SLE_CastShadow::GetValue)
		]
		]
		];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLE_CastShadow::GetValue(ECheckBoxState NewCheckboxState) {
	FPropertyChangedEvent PropEditEvent(ULightComponent::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(ULightComponent, CastShadows))); //line 412
	Item->Modify();
	Item->GetLightComponent()->InvalidateLightingCache();
	bool xx = NewCheckboxState == ECheckBoxState::Checked ? 1 : 0;
	Item->GetLightComponent()->SetCastShadows(xx);
	Item->GetLightComponent()->MarkRenderStateDirty();
	Item->GetLightComponent()->PostEditChangeProperty(PropEditEvent);
}


ECheckBoxState SLE_CastShadow::EnableCastShadow() const {
	FPropertyChangedEvent PropEditEvent(ULightComponent::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(ULightComponent, CastShadows))); //line 412
	ECheckBoxState IsCastShadow = Item->GetLightComponent()->CastShadows ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;

	return IsCastShadow;
}

FLinearColor SLE_CastShadow::GetColor() const {
	if (!Item.IsValid()) { return FLinearColor::Black; }
	//
	return Item->GetLightColor();
}

void SLE_CastShadow::SetColor(FLinearColor NewColor) {
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


void SLE_CastShadow::OnInteractivePickEnd() {}
void SLE_CastShadow::OnInteractivePickBegin() {}
void SLE_CastShadow::OnColorPickerClosed(const TSharedRef<SWindow>& Window) {}

void SLE_CastShadow::OnColorPickerCancelled(FLinearColor OriginalColor) {
	if (!Item.IsValid()) { return; }
	//
	Item->SetLightColor(OriginalColor);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FReply SLE_CastShadow::OnClickedItem(const FGeometry& Geometry, const FPointerEvent& MouseEvent) {
	if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
	if (!Item.IsValid()) { return FReply::Unhandled(); }
	//
	FColorPickerArgs PickerArgs; {
		PickerArgs.bUseAlpha = true;
		PickerArgs.bOnlyRefreshOnOk = false;
		PickerArgs.bOnlyRefreshOnMouseUp = false;
		PickerArgs.DisplayGamma = TAttribute<float>::Create(TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
		PickerArgs.OnColorPickerCancelled = FOnColorPickerCancelled::CreateSP(this, &SLE_CastShadow::OnColorPickerCancelled);
		PickerArgs.OnInteractivePickBegin = FSimpleDelegate::CreateSP(this, &SLE_CastShadow::OnInteractivePickBegin);
		PickerArgs.OnColorPickerWindowClosed = FOnWindowClosed::CreateSP(this, &SLE_CastShadow::OnColorPickerClosed);
		PickerArgs.OnInteractivePickEnd = FSimpleDelegate::CreateSP(this, &SLE_CastShadow::OnInteractivePickEnd);
		PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &SLE_CastShadow::SetColor);
		PickerArgs.InitialColorOverride = Item->GetLightColor();
		PickerArgs.ParentWidget = ColorBlock;
	} OpenColorPicker(PickerArgs);
	//
	return FReply::Handled();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SLE_CastShadow::IsInteractable() const {
	return IsEnabled();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
