#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include <ContentBrowserDelegates.h>
#include "IContentBrowserSingleton.h"
#include <Widgets/SWindow.h>
#include <../Private/SPathPicker.h>
#include <../Private/SAssetPicker.h>
#include "AssetData.h"
#include <../Private/SDetailSingleItemRow.h>

class SContentSlate : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SContentSlate){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	FReply CopyMaterialInstance();
	FReply CreateMaterialInstance();
	FString AssetPath;
	//void UpdateInputValidity();
	TArray<FAssetData> AssetDatas;
	TSharedPtr<SEditableTextBox> MNptr;
	TSharedPtr<SEditableTextBox> MPathptr;
	//void RequestUseActiveTimer();

private:
	//void HandleAssetViewFolderEntered(const FString& NewPath);
	//void SetCurrentlySelectedPath(const FString& NewPath);
	//FSetPathPickerPathsDelegate SetPathsDelegate;
	TArray<FName> AssetClassNames;
	FString CurrentlySelectedPath;
	void GetAssetData(FString& InFilterPackagePath, TArray<FAssetData>& OutAssetData);
	void OnPathChange(const FString& NewPath);
	void HandlePathSelected(const FString& NewPath);
	void SetCurrentlySelectedPath(const FString& NewPath);

	TSharedPtr<SPathPicker> PathPicker;
	TSharedPtr<SAssetPicker> AssetPicker;

	FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;
	FSetARFilterDelegate SetFilterDelegate;

	FOnPathSelected OnPathSelected;

	//TSharedPtr<SDetailSingleItemRow> DetailsView;
	
	//EActiveTimerReturnType HadleActiveTimer(double InCurrentTime, float InDeltaTime);
	//void CancelActiveTimer();
	//TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;
	//int32 Count;

};
