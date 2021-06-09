#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/Slate/Public/Widgets/Input/SNumericEntryBox.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"
#include "Engine/SkyLight.h"



class SLE_Intensity_Sky : public SCompoundWidget {
private:
	TWeakObjectPtr<ASkyLight>Item;
	TSharedPtr<SColorBlock>ColorBlock;
public:
	SLE_Intensity_Sky();
	virtual ~SLE_Intensity_Sky() override;

	SLATE_BEGIN_ARGS(SLE_Intensity_Sky) {}
	SLATE_END_ARGS()

		void Construct(const FArguments &InArgs, ASkyLight* Target);
	
	void OnValueChanged(float FloatValue) const;
	
	TOptional<float> GetValue() const;
};
