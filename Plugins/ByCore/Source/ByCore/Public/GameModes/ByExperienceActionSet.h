// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ByExperienceActionSet.generated.h"

class UGameFeatureAction;

/**
 * 
 */
UCLASS(BlueprintType, NotBlueprintable)
class BYCORE_API UByExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// List of Game Feature Plugins this experience wants to have active
	UPROPERTY(EditAnywhere, Category="Feature Dependencies")
	TArray<FString> GameFeaturesToEnable;
	
	// List of actions to perform as this experience is loaded/activated/deactivated/unloaded
	UPROPERTY(EditAnywhere, Instanced, Category="Actions to Perform")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
