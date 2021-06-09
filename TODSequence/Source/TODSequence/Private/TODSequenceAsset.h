#pragma once
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

class TODSequenceAsset
{
public:
	void CreateNewTODSequece();
	void UpdateTODSequece();
	void CheckTODSequeceExist();
	void NameTODSequence();

private:
	UGameplayStatics TODWorld;
};