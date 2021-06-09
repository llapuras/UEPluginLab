#include "ContentSlate.h"
#include "CreateMaterialInstance.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Internationalization/Text.h"
#include "Widgets/Layout/SSplitter.h"
#include <ContentBrowserDelegates.h>
#include <ContentBrowserModule.h>
#include "IContentBrowserSingleton.h"
#include <Logging/LogMacros.h>
#include <AssetRegistry/AssetRegistryModule.h>


#define LOCTEXT_NAMESPACE "ContentSlate"

void SContentSlate::Construct(const FArguments& InArgs)
{
	AssetPath= TEXT("/MaterialLibrary");

	//const FText DefaultPath = FText::FromString(FPackageName::GetLongPackagePath(InArgs._DefaultPath.ToString()));
	
	FOpenAssetDialogConfig InConfig;
	AssetClassNames = InConfig.AssetClassNames;
	const FString DefaultPath = InConfig.DefaultPath;
	//UE_LOG(LogTemp, Log, TEXT("Default Path "), FString(*DefaultPath));

	FPathPickerConfig PathPickerConfig;
	PathPickerConfig.DefaultPath = AssetPath;
	PathPickerConfig.bAddDefaultPath = true;
	PathPickerConfig.OnPathSelected = FOnPathSelected::CreateSP(this, &SContentSlate::HandlePathSelected);
	//PathPickerConfig.SetPathsDelegates.Add(&SetPathsDelegate);

	FAssetPickerConfig AssetPickerConfig;
	AssetPickerConfig.Filter.ClassNames.Add(UMaterial::StaticClass()->GetFName());
	//AssetPickerConfig.Filter.ClassNames.
	//AssetPickerConfig.Filter.PackagePaths.Add(FName(*DefaultPath));
	AssetPickerConfig.Filter.PackagePaths.Add(TEXT("/MaterialLibrary/"));
	AssetPickerConfig.SetFilterDelegates.Add(&SetFilterDelegate);
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::Tile;
	AssetPickerConfig.bShowPathInColumnView = true;
	AssetPickerConfig.bShowTypeInColumnView = false;
	AssetPickerConfig.bAllowDragging = true;
	AssetPickerConfig.bAllowNullSelection = false;
	AssetPickerConfig.bCanShowFolders = false;
	AssetPickerConfig.bAddFilterUI = true;
	AssetPickerConfig.Filter.ClassNames.Add(UMaterialInterface::StaticClass()->GetFName());
	AssetPickerConfig.GetCurrentSelectionDelegates.Add(&GetCurrentSelectionDelegate);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	PathPicker = StaticCastSharedRef<SPathPicker>(ContentBrowserModule.Get().CreatePathPicker(PathPickerConfig));
	AssetPicker = StaticCastSharedRef<SAssetPicker>(ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig));

	OnPathSelected = InConfig.OnPathSelected;
	
	//AssetPickerConfig.OnShouldFilterAsset = FOnShouldFilterAsset::CreateLambda([this](const FAssetData) {return false; });

	SetCurrentlySelectedPath(DefaultPath);

	//testrow = StaticCastSharedRef<SDetailSingleItemRow>();

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().Padding(5.0f).VAlign(VAlign_Top)
			[
				SNew(SVerticalBox)
			  +SVerticalBox::Slot()
				[
					SNew(SHorizontalBox)
				    +SHorizontalBox::Slot()
					.Padding(5.0f).VAlign(VAlign_Top)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("Material Name")))
					]
					+ SHorizontalBox::Slot()
					.Padding(1.0f).VAlign(VAlign_Top)
					[
						SAssignNew(MNptr, SEditableTextBox)
						.HintText(LOCTEXT("Material Name", " Material Nick Name"))
					]
				]

					+ SVerticalBox::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(5.0f).VAlign(VAlign_Top)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Destination Path")))
						]
						+ SHorizontalBox::Slot()
						.Padding(1.0f).VAlign(VAlign_Top)
						[
							SAssignNew(MPathptr, SEditableTextBox)
							.HintText(LOCTEXT("Destination Path", " MaterialLab "))
						]
					]
			
			]

			+ SVerticalBox::Slot().FillHeight(5.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth()
				[
					SNew(SBorder)
					.Content()
				[
					PathPicker.ToSharedRef()
				]
				]
			+ SHorizontalBox::Slot()
				[
					SNew(SBorder)
					.Content()
				[
					AssetPicker.ToSharedRef()
				]
				]
			]
			+ SVerticalBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().MaxWidth(256)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Create New Instance")))
				.OnClicked_Raw(this, &SContentSlate::CreateMaterialInstance)
				]
			+ SHorizontalBox::Slot().MaxWidth(256)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Copy Current Instance")))
				.OnClicked_Raw(this, &SContentSlate::CopyMaterialInstance)
				]
				]
		];
}

FReply SContentSlate::CopyMaterialInstance()
{

	AssetDatas = GetCurrentSelectionDelegate.Execute();

	//FString MName = MNptr->GetText().ToString();
	for (int i = 0; i < AssetDatas.Num(); i++)
	{
		FCreateMaterialInstance CMI;
		CMI.CopyMaterialInstanceMaster(AssetDatas[i]);
	}
	UE_LOG(LogClass, Log, TEXT("Copy!"));

	return FReply::Handled();
}

FReply SContentSlate::CreateMaterialInstance()
{
	AssetDatas = GetCurrentSelectionDelegate.Execute();
	FString MName = MNptr->GetText().ToString();
	FString MPath = MPathptr->GetText().ToString();

	for (int i = 0; i < AssetDatas.Num(); i++)
	{
		FCreateMaterialInstance CMI;
		CMI.CreateMaterialInstanceMaster(AssetDatas[i], MName, MPath);
	}
	return FReply::Handled();
}

void SContentSlate::OnPathChange(const FString& NewPath)
{
	AssetPath = NewPath;
}

void SContentSlate::GetAssetData(FString& InFilterPackagePath, TArray<FAssetData>& OutAssetData)
{
	OutAssetData.Reset();
	FARFilter Filter;
	Filter.bIncludeOnlyOnDiskAssets = true;
	Filter.bRecursivePaths = true;

	FString ValidFilterPackageName = InFilterPackagePath;
	while (ValidFilterPackageName.EndsWith("/"))
	{
		ValidFilterPackageName.RemoveAt(ValidFilterPackageName.Len() - 1);
	}

	Filter.PackagePaths.AddUnique(*ValidFilterPackageName);

	FAssetRegistryModule& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	//TArray<FAssetData> OutAssetData;
	AssetRegistry.Get().GetAssets(Filter, OutAssetData);

}

void SContentSlate::HandlePathSelected(const FString& NewPath)
{
	FARFilter NewFilter;

	NewFilter.ClassNames.Append(AssetClassNames);
	NewFilter.PackagePaths.Add(FName(*NewPath));

	SetCurrentlySelectedPath(NewPath);

	SetFilterDelegate.ExecuteIfBound(NewFilter);
}

void SContentSlate::SetCurrentlySelectedPath(const FString& NewPath)
{
	CurrentlySelectedPath = NewPath;

	OnPathSelected.ExecuteIfBound(NewPath);
}

#undef LOCTEXT_NAMESPACE

