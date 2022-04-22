// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "GameModes/ByWorldSettingsBase.h"
#include "GameModes/ByExperienceDefinition.h"
#include "Engine/AssetManager.h"

FPrimaryAssetId AByWorldSettingsBase::GetExperienceDefinition() const
{
	FPrimaryAssetId Result;

	if (ExperienceDefinition.IsValid())
	{
		Result = UAssetManager::Get().GetPrimaryAssetIdForPath(ExperienceDefinition.ToSoftObjectPath());
	}
	
	return Result;
}
