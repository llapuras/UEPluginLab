#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"

#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/Slate/Public/Widgets/Input/SNumericEntryBox.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"



class SLE_Intensity : public SCompoundWidget {
private:
	TWeakObjectPtr<ALight>Item;
	TSharedPtr<SColorBlock>ColorBlock;
public:
	SLE_Intensity();
	virtual ~SLE_Intensity() override;
	//
	SLATE_BEGIN_ARGS(SLE_Intensity) {}
	SLATE_END_ARGS()
	//
	void Construct(const FArguments& InArgs, ALight* Target);
	//
	void OnValueChanged(float FloatValue) const;
	//
	TOptional<float> GetValue() const;
};
