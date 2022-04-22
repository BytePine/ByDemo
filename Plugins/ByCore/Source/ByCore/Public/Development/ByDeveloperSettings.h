// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ByDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, meta=(DisplayName=ByCore))
class BYCORE_API UByDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Get UByDeveloperSettings Default Object */
	static UByDeveloperSettings* Get();
	
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override;

public:
	UPROPERTY(EditDefaultsOnly, Category=GameMode)
	TSoftClassPtr<class UByExperienceDefinition> DefaultExperienceDefinition;
};
