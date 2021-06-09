#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"

#include "Runtime/Slate/Public/Widgets/Layout/SBox.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/SlateCore/Public/Widgets/Images/SImage.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"
#include "Engine/SkyLight.h"


class SLE_List_Sky : public SCompoundWidget {
private:
	TWeakObjectPtr<ASkyLight>Item;
public:
	SLE_List_Sky();
	virtual ~SLE_List_Sky() override;
	
	SLATE_BEGIN_ARGS(SLE_List_Sky) {}
	SLATE_END_ARGS()
		
		
		void Construct(const FArguments &InArgs, ASkyLight* Target);
	
	virtual bool IsInteractable() const override;
	
	FReply OnClickedItem();
	
	FText GetTypeTooltip() const;
	const FSlateBrush* GetTypeBrush() const;
};


