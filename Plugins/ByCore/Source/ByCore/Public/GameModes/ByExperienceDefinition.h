// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ByExperienceDefinition.generated.h"

class UGameFeatureAction;
class UByExperienceActionSet;

/**
 * 
 */
UCLASS(BlueprintType, Const)
class BYCORE_API UByExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// List of Game Feature Plugins this experience wants to have active
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;

	// List of actions to perform as this experience is loaded/activated/deactivated/unloaded
	UPROPERTY(EditDefaultsOnly, Instanced, Category=Actions)
	TArray<TObjectPtr<UGameFeatureAction>> Actions;

	// List of additional action sets to compose into this experience
	UPROPERTY(EditDefaultsOnly, Instanced, Category=Actions)
	TArray<TObjectPtr<UByExperienceActionSet>> ActionSets;
};
