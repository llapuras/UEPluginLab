#pragma once
#include "MaterialLibrary.h"

class FCreateMaterialInstance
{
public:
	//FReply CreateMaterialInstance();
	void CreateMaterialInstanceMaster(FAssetData AssetData, FString MName, FString PPath);
	void CopyMaterialInstanceMaster(FAssetData AssetData);
	void SetMaterialInstanceStaticSwitchParameterValue(UMaterialInstance* Instance, FName ParameterName, bool Value);
};