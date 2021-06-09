#include "CreateMaterialInstance.h"
#include "ContentSlate.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetToolsModule.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"

/*FReply FCreateMaterialInstance::CreateMaterialInstance()
{
	CreateMaterialInstanceMaster("tag");
	return FReply::Handled();
}*/

void FCreateMaterialInstance::CreateMaterialInstanceMaster(FAssetData AssetData, FString MName, FString PPath)
{
		UE_LOG(LogClass, Log, TEXT("Selected: %s"), *AssetData.ObjectPath.ToString());
		//Material Instance Constant
		FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
		//FString tag = TEXT("Test");
		FString PackageName = AssetData.ObjectPath.ToString();
		//FString MaterialName = "MI_" + tag + "_" + AssetData.AssetName.ToString();
		FString MaterialName = "MI_" + MName;
		FString PathName = AssetData.PackagePath.ToString();
		//FString NewPath = TEXT("/Game/MaterialLab");
		FString NewPath = "/Game/" + PPath;
		const TCHAR* package = *PackageName;
		const TCHAR* path = *PathName;
		const TCHAR* name = *AssetData.AssetName.ToString();

		UMaterial* ParentMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, package));

		if (ParentMaterial != nullptr)
		{
			UMaterialInterface* materialInterface = (UMaterialInterface*)ParentMaterial;
			UMaterialInstanceConstantFactoryNew* MIFactory = NewObject<UMaterialInstanceConstantFactoryNew>();
			MIFactory->InitialParent = materialInterface;

			UObject* NewAsset = AssetToolsModule.Get().CreateAsset(MaterialName, NewPath, UMaterialInstanceConstant::StaticClass(), MIFactory);
			UMaterialInstanceConstant* Instance = (UMaterialInstanceConstant*)NewAsset;
			//UMaterialInstanceConstant* UnrealMaterialConstant = (UMaterialInstanceConstant*)MIFactory->FactoryCreateNew(UMaterialInstanceConstant::StaticClass(), Package, *MaterialFullName, RF_Standalone | RF_Public, NULL, GWarn);

			if (Instance != nullptr)
			{
				Instance->SetScalarParameterValueEditorOnly(FMaterialParameterInfo("Metallic Intensity"), 0.0f);

				SetMaterialInstanceStaticSwitchParameterValue(Instance, "Desaturate", true);

				Instance->MarkPackageDirty();
				Instance->PostEditChange();
			}
		}
	
}

void FCreateMaterialInstance::SetMaterialInstanceStaticSwitchParameterValue(UMaterialInstance* Instance, FName ParameterName, bool Value)
{
	check(GIsEditor || IsRunningCommandlet());

	FStaticParameterSet StaticParameters;
	Instance->GetStaticParameterValues(StaticParameters);
	for (auto& SwitchParameter : StaticParameters.StaticSwitchParameters)
	{
		UE_LOG(LogClass, Log, TEXT("Run"));
		if (SwitchParameter.ParameterInfo.Name == ParameterName)
		{
			SwitchParameter.Value = Value;
			SwitchParameter.bOverride = true;
		}
	}
	Instance->UpdateStaticPermutation(StaticParameters);
}

void FCreateMaterialInstance::CopyMaterialInstanceMaster(FAssetData AssetData)
{
	UE_LOG(LogClass, Log, TEXT("Selected: %s"), *AssetData.ObjectPath.ToString());
	//Material Instance Constant
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FString tag = TEXT("Test");
	FString PackageName = AssetData.ObjectPath.ToString();
	FString MaterialName = "CMI_" + tag + "_" + AssetData.AssetName.ToString();
	FString PathName = AssetData.PackagePath.ToString();
	FString NewPath = TEXT("/Game/MaterialLab");

	const TCHAR* package = *PackageName;
	const TCHAR* path = *PathName;
	const TCHAR* name = *AssetData.AssetName.ToString();

	UMaterialInstance* ParentMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), NULL, package));

	if (ParentMaterial != nullptr)
	{
		UMaterialInterface* materialInterface = (UMaterialInterface*)ParentMaterial;
		UMaterialInstanceConstantFactoryNew* MIFactory = NewObject<UMaterialInstanceConstantFactoryNew>();
		MIFactory->InitialParent = materialInterface;

		UObject* NewAsset = AssetToolsModule.Get().CreateAsset(MaterialName, NewPath, UMaterialInstanceConstant::StaticClass(), MIFactory);
		UMaterialInstanceConstant* Instance = (UMaterialInstanceConstant*)NewAsset;
		//UMaterialInstanceConstant* UnrealMaterialConstant = (UMaterialInstanceConstant*)MIFactory->FactoryCreateNew(UMaterialInstanceConstant::StaticClass(), Package, *MaterialFullName, RF_Standalone | RF_Public, NULL, GWarn);

		if (Instance != nullptr)
		{
			Instance->MarkPackageDirty();
			Instance->PostEditChange();
		}
	}

}