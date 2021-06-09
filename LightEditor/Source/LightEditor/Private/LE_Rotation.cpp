#include "LE_Rotation.h"
#include "Components/LightComponent.h"

#define LOCTEXT_NAMESPACE "Synaptech"

SLE_Rotation::SLE_Rotation() {}
SLE_Rotation::~SLE_Rotation() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLE_Rotation::Construct(const FArguments& InArgs, ALight* Target) {
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
			SNew(SRotatorInputBox)
			.Roll(this, &SLE_Rotation::GetValueRoll)
		.Pitch(this, &SLE_Rotation::GetValuePitch)
		.Yaw(this, &SLE_Rotation::GetValueYaw)
		.AllowResponsiveLayout(true)
		.bColorAxisLabels(true)
		//.IsEnabled(this, &SLE_Rotation::GetIsEnabled)
		//.OnBeginSliderMovement(this, &SLE_Rotation::OnBeginRotationSlider)
		//.OnEndSliderMovement(this, &SLE_Rotation::OnEndRotationSlider)
		.OnRollChanged(this, &SLE_Rotation::OnValueChangedRoll)
		.OnPitchChanged(this, &SLE_Rotation::OnValueChangedPitch)
		.OnYawChanged(this, &SLE_Rotation::OnValueChangedYaw)
		/*SNew(SNumericEntryBox<float>)
		.MinSliderValue(0.0f)
		.MaxSliderValue(359.999f)
		.OnValueChanged(this, &SLE_Rotation::OnValueChangedPitch)
	.Value(this, &SLE_Rotation::GetValuePitch)
	.AllowSpin(true)*/
		]
		]
		];
}

void SLE_Rotation::OnValueChangedPitch(float FloatValuePitch) const {
	if (!Item.IsValid()) { return; }
	//
	FPropertyChangedEvent PropEditEvent(AActor::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(AActor, K2_GetActorRotation())));
	EComponentMobility::Type Mobility = Item->K2_GetRootComponent()->Mobility;
	//

	FRotator NewComponentValuex = FRotator(FloatValuePitch, GetRotator().Yaw, GetRotator().Roll);

	Item->K2_GetRootComponent()->SetRelativeRotation(NewComponentValuex);


}

void SLE_Rotation::OnValueChangedYaw(float FloatValueYaw) const
{
	if (!Item.IsValid()) { return; }
	//
	FPropertyChangedEvent PropEditEvent(AActor::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(AActor, K2_GetActorRotation())));
	EComponentMobility::Type Mobility = Item->K2_GetRootComponent()->Mobility;
	//

	FRotator NewComponentValuey = FRotator(GetRotator().Pitch, FloatValueYaw, GetRotator().Roll);
	Item->Modify();
	Item->K2_GetRootComponent()->Mobility = EComponentMobility::Stationary;
	//Item->K2_GetRootComponent()->InvalidateLightingCache();
	Item->K2_GetRootComponent()->SetRelativeRotation(NewComponentValuey);
	Item->K2_GetRootComponent()->MarkRenderStateDirty();
	//
	Item->K2_GetRootComponent()->PostEditChangeProperty(PropEditEvent);
	Item->K2_GetRootComponent()->Mobility = Mobility;

}

void SLE_Rotation::OnValueChangedRoll(float FloatValueRoll) const
{
	if (!Item.IsValid()) { return; }
	//
	FPropertyChangedEvent PropEditEvent(AActor::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(AActor, K2_GetActorRotation())));
	EComponentMobility::Type Mobility = Item->K2_GetRootComponent()->Mobility;
	//

	FRotator NewComponentValuez = FRotator(GetRotator().Pitch, GetRotator().Yaw, FloatValueRoll);
	Item->Modify();
	Item->K2_GetRootComponent()->Mobility = EComponentMobility::Stationary;
	//Item->K2_GetRootComponent()->InvalidateLightingCache();
	Item->K2_GetRootComponent()->SetRelativeRotation(NewComponentValuez);
	Item->K2_GetRootComponent()->MarkRenderStateDirty();
	//
	Item->K2_GetRootComponent()->PostEditChangeProperty(PropEditEvent);
	Item->K2_GetRootComponent()->Mobility = Mobility;

}




TOptional<float> SLE_Rotation::GetValuePitch() const {
	if (!Item.IsValid()) { return 0.f; }
	//
	return Item->GetActorRotation().Pitch;
}
TOptional<float> SLE_Rotation::GetValueYaw() const {
	if (!Item.IsValid()) { return 0.f; }
	//
	return Item->GetActorRotation().Yaw;
}
TOptional<float> SLE_Rotation::GetValueRoll() const {
	if (!Item.IsValid()) { return 0.f; }
	//
	return Item->GetActorRotation().Roll;
}



FRotator SLE_Rotation::GetRotator() const {
	if (!Item.IsValid()) { return FRotator::ZeroRotator; }

	return Item->GetActorRotation();
}
#undef LOCTEXT_NAMESPACE










//
