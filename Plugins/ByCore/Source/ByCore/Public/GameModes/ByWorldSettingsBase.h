// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "ByWorldSettingsBase.generated.h"

class UByExperienceDefinition;

/**
 * 
 */
UCLASS(Abstract)
class BYCORE_API AByWorldSettingsBase : public AWorldSettings
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetExperienceDefinition() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category=GameMode)
	TSoftClassPtr<UByExperienceDefinition> ExperienceDefinition;
};
