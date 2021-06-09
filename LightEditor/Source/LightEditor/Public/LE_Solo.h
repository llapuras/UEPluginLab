#pragma once

#include "LightEditor.h"
#include "LightEditorStyle.h"

#include "Components/LightComponent.h"

#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Runtime/SlateCore/Public/Widgets/Images/SImage.h"

#include "Editor/EditorEngine.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"

class SLE_Solo : public SImage {
private:
	static TArray<TWeakObjectPtr<ALight>>ActiveList;
private:
	bool Solo = false;
	TWeakObjectPtr<ALight>Item;
private:
	FReply HandleClick() {
		if (!Item.IsValid()) {
			return FReply::Unhandled();
		}
		SetSolo(!IsVisible());
		
		return FReply::Handled();
	}
	virtual FReply OnMouseButtonDoubleClick(const FGeometry &InMyGeometry, const FPointerEvent& InMouseEvent) override {
		return HandleClick();
	}
	virtual FReply OnMouseButtonDown(const FGeometry &MyGeometry, const FPointerEvent& MouseEvent) override {
		if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton) {
			return FReply::Unhandled();
		} return HandleClick();
	}
	virtual FReply OnMouseButtonUp(const FGeometry &MyGeometry, const FPointerEvent& MouseEvent) override {
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
			return FReply::Handled();
		} return FReply::Unhandled();
	}
	const FSlateBrush* GetBrush() const {
		if (IsVisible()) {
			static const FName NAME_VisibleHoveredBrush = TEXT("Level.VisibleHighlightIcon16x");
			static const FName NAME_VisibleNotHoveredBrush = TEXT("Level.VisibleIcon16x");
			
			return IsHovered() ? FEditorStyle::GetBrush(NAME_VisibleHoveredBrush) : FEditorStyle::GetBrush(NAME_VisibleNotHoveredBrush);
		}
		else {
			static const FName NAME_NotVisibleHoveredBrush = TEXT("Level.NotVisibleHighlightIcon16x");
			static const FName NAME_NotVisibleNotHoveredBrush = TEXT("Level.NotVisibleIcon16x");
			
			return IsHovered() ? FEditorStyle::GetBrush(NAME_NotVisibleHoveredBrush) : FEditorStyle::GetBrush(NAME_NotVisibleNotHoveredBrush);
		}
	}
	bool IsVisible() const {
		if (Item.IsStale()) { return false; }
		
		auto World = Item.Get()->GetWorld();
		for (TActorIterator<ALight>Actor(World); Actor; ++Actor) {
			if ((*Actor)->HasAnyFlags(RF_BeginDestroyed)) { continue; }
			if ((*Actor) == Item.Get()) { continue; }
			
			if (Actor->GetLightComponent()->bAffectsWorld) { return false; }
		}
		return (Solo && (Item->GetLightComponent()->bAffectsWorld));
	}
	void SetSolo(const bool DoSolo);
	void SetLightActive(ALight* Target, const bool Active);
public:
	SLATE_BEGIN_ARGS(SLE_Solo) {}
	SLATE_END_ARGS()
		
		void Construct(const FArguments &InArgs, ALight* Target);
};