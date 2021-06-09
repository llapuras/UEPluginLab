#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"

#include "Runtime/Slate/Public/Widgets/Layout/SBox.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/SlateCore/Public/Widgets/Images/SImage.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SLE_List : public SCompoundWidget {
private:
	TWeakObjectPtr<ALight>Item;
public:
	SLE_List();
	virtual ~SLE_List() override;
	//
	SLATE_BEGIN_ARGS(SLE_List) {}
	SLATE_END_ARGS()
		//
		//
		void Construct(const FArguments& InArgs, ALight* Target);
	//
	virtual bool IsInteractable() const override;
	//
	FReply OnClickedItem();
	//
	FText GetTypeTooltip() const;
	const FSlateBrush* GetTypeBrush() const;
};
