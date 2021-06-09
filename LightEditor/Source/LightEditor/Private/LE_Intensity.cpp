#include "LE_Intensity.h"
#include "Components/LightComponent.h"

#define LOCTEXT_NAMESPACE "Synaptech"

SLE_Intensity::SLE_Intensity() {}
SLE_Intensity::~SLE_Intensity() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLE_Intensity::Construct(const FArguments& InArgs, ALight* Target) {
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
					SNew(SNumericEntryBox<float>)
					.OnValueChanged(this, &SLE_Intensity::OnValueChanged)
					.Value(this, &SLE_Intensity::GetValue)
					.AllowSpin(true)
				]
			]
		];
}

void SLE_Intensity::OnValueChanged(float FloatValue) const {
	if (!Item.IsValid()) { return; }
	//
	FPropertyChangedEvent PropEditEvent(ULightComponent::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(ULightComponent, Intensity)));
	EComponentMobility::Type Mobility = Item->GetLightComponent()->Mobility;
	//
	Item->Modify();
	Item->GetLightComponent()->Mobility = EComponentMobility::Stationary;
	Item->GetLightComponent()->InvalidateLightingCache();
	Item->GetLightComponent()->SetIntensity(FloatValue);
	Item->GetLightComponent()->MarkRenderStateDirty();
	//
	Item->GetLightComponent()->PostEditChangeProperty(PropEditEvent);
	Item->GetLightComponent()->Mobility = Mobility;

}

TOptional<float> SLE_Intensity::GetValue() const {
	if (!Item.IsValid()) { return 0.f; }
	//
	return Item->GetLightComponent()->Intensity;
}


#undef LOCTEXT_NAMESPACE










//
