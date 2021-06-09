
#include "LE_Color_Sky.h"

#include "Components/SkyLightComponent.h"
#include "Runtime/Core/Public/Misc/Attribute.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"

#define LOCTEXT_NAMESPACE "Synaptech"
#define PLUGIN_NAME TEXT("LightEditor")

SLE_Color_Sky::SLE_Color_Sky() {}
SLE_Color_Sky::~SLE_Color_Sky() {}


void SLE_Color_Sky::Construct(const FArguments &InArgs, ASkyLight* Target) {
	Item = Target;

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
			.OnMouseButtonDown(this, &SLE_Color_Sky::OnClickedItem)
		.Color(this, &SLE_Color_Sky::GetColor)
		.IgnoreAlpha(false)
		]
		]
		];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FLinearColor SLE_Color_Sky::GetColor() const {
	if (!Item.IsValid()) { return FLinearColor::Black; }
	//
	return Item->GetLightComponent()->GetLightColor();
}

void SLE_Color_Sky::SetColor(FLinearColor NewColor) {
	if (!Item.IsValid()) { return; }
	//
	FPropertyChangedEvent PropEditEvent(USkyLightComponent::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(USkyLightComponent, LightColor)));
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLE_Color_Sky::OnInteractivePickEnd() {}
void SLE_Color_Sky::OnInteractivePickBegin() {}
void SLE_Color_Sky::OnColorPickerClosed(const TSharedRef<SWindow> &Window) {}

void SLE_Color_Sky::OnColorPickerCancelled(FLinearColor OriginalColor) {
	if (!Item.IsValid()) { return; }
	//
	Item->GetLightComponent()->LightColor = OriginalColor.ToFColor(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FReply SLE_Color_Sky::OnClickedItem(const FGeometry &Geometry, const FPointerEvent &MouseEvent) {
	if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
	if (!Item.IsValid()) { return FReply::Unhandled(); }
	//
	FColorPickerArgs PickerArgs; {
		PickerArgs.bUseAlpha = true;
		PickerArgs.bOnlyRefreshOnOk = false;
		PickerArgs.bOnlyRefreshOnMouseUp = false;
		PickerArgs.DisplayGamma = TAttribute<float>::Create(TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
		PickerArgs.OnColorPickerCancelled = FOnColorPickerCancelled::CreateSP(this, &SLE_Color_Sky::OnColorPickerCancelled);
		PickerArgs.OnInteractivePickBegin = FSimpleDelegate::CreateSP(this, &SLE_Color_Sky::OnInteractivePickBegin);
		PickerArgs.OnColorPickerWindowClosed = FOnWindowClosed::CreateSP(this, &SLE_Color_Sky::OnColorPickerClosed);
		PickerArgs.OnInteractivePickEnd = FSimpleDelegate::CreateSP(this, &SLE_Color_Sky::OnInteractivePickEnd);
		PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &SLE_Color_Sky::SetColor);
		PickerArgs.InitialColorOverride = Item->GetLightComponent()->GetLightColor();
		PickerArgs.ParentWidget = ColorBlock;
	} OpenColorPicker(PickerArgs);
	//
	return FReply::Handled();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SLE_Color_Sky::IsInteractable() const {
	return IsEnabled();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////