#include "LE_List_Sky.h"
#include "Engine/SkyLight.h"


#define LOCTEXT_NAMESPACE "Synaptech"

SLE_List_Sky::SLE_List_Sky() {}
SLE_List_Sky::~SLE_List_Sky() {}

void SLE_List_Sky::Construct(const FArguments &InArgs, ASkyLight* Target) {
	TSharedRef<SButton>Button = SNew(SButton);
	FText Caption = FText::FromString(TEXT(""));
	
	Item = Target;
	if (Item.IsValid()) { Caption = FText::FromString(Item->GetActorLabel()); }
	
	SAssignNew(Button, SButton)
		.ButtonStyle(FEditorStyle::Get(), "FlatButton.Default")
		.ForegroundColor(FSlateColor::UseForeground())
		.OnClicked(this, &SLE_List_Sky::OnClickedItem)
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SImage)
			.Image(this, &SLE_List_Sky::GetTypeBrush)
		.ToolTipText(this, &SLE_List_Sky::GetTypeTooltip)
		]
	+ SHorizontalBox::Slot().Padding(2)
		.HAlign(HAlign_Fill).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Margin(FMargin(2))
			.Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
		.Justification(ETextJustify::Center)
		.Text(Caption)
		]
		];

	ChildSlot
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBox).Padding(FMargin(4))
			[
				Button
			]
		];
}

FReply SLE_List_Sky::OnClickedItem() {
	if (GEditor && Item.IsValid()) {
		GEditor->SelectNone(true, true, true);
		GEditor->SelectActor(Item.Get(), true, true, true, true);
		
		TArray<AActor*>Actors; Actors.Add(Item.Get());
		GEditor->MoveViewportCamerasToActor(Actors, true);
	}
	return FReply::Handled();
}



FText SLE_List_Sky::GetTypeTooltip() const {
	return FText::FromString(TEXT("Sky Light Source"));
}

const FSlateBrush* SLE_List_Sky::GetTypeBrush() const {
	return FLightEditorStyle::Get()->GetBrush(TEXT("LE.Sky"));
}



bool SLE_List_Sky::IsInteractable() const {
	return IsEnabled();
}



#undef LOCTEXT_NAMESPACE

