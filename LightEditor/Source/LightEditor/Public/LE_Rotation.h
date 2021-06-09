#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"

#include "Widgets/Input/SRotatorInputBox.h"

#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/Slate/Public/Widgets/Input/SNumericEntryBox.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"



class SLE_Rotation : public SCompoundWidget {
private:
	TWeakObjectPtr<AActor>Item;
	TSharedPtr<SColorBlock>ColorBlock;
public:
	SLE_Rotation();
	virtual ~SLE_Rotation() override;
	//
	SLATE_BEGIN_ARGS(SLE_Rotation) {}
	SLATE_END_ARGS()
		//
		//
		void Construct(const FArguments& InArgs, ALight* Target);
	//
	void OnValueChangedPitch(float FloatValuePitch) const;
	void OnValueChangedYaw(float FloatValueYaw) const;
	void OnValueChangedRoll(float FloatValueRoll) const;

	//void OnValueChanged(FRotator ChangRotator);
	//
	TOptional<float> GetValuePitch() const;
	TOptional<float> GetValueYaw() const;
	TOptional<float> GetValueRoll() const;
	//TOptional<FRotator> GetValue();
	FRotator GetRotator() const;
};