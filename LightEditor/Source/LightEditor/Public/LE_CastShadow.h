#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"

#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Runtime/SlateCore/Public/Widgets/SWindow.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/SlateCore/Public/Widgets/Images/SImage.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"
#include "Engine/Light.h"

class SLE_CastShadow : public SCompoundWidget {
private:
	TWeakObjectPtr<ALight>Item;
	TSharedPtr<SColorBlock>ColorBlock;
	TSharedPtr<SCheckBox>EnableShadow;
public:
	SLE_CastShadow();
	virtual ~SLE_CastShadow() override;
	//
	SLATE_BEGIN_ARGS(SLE_CastShadow) {} //?
	SLATE_END_ARGS()
	//
	void Construct(const FArguments& InArgs, ALight* Target);
	//
	virtual bool IsInteractable() const override;
	//
	void OnInteractivePickEnd();
	void OnInteractivePickBegin();
	void OnColorPickerCancelled(FLinearColor OriginalColor);
	void OnColorPickerClosed(const TSharedRef<SWindow>& Window);
	//
	FReply OnClickedItem(const FGeometry& Geometry, const FPointerEvent& MouseEvent);
	//
	void SetColor(FLinearColor NewColor);
	//
	FLinearColor GetColor() const;
	//
	ECheckBoxState EnableCastShadow() const;

	void GetValue(ECheckBoxState NewCheckboxState);
};