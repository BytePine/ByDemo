// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ByVersionMinimal.h"
#include "ByVersionObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BYDEMO_API UByVersionObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FByVSoftObjectPath VSoftObjectPath;

	UPROPERTY(EditAnywhere)
	FSoftObjectPath SoftObjectPath;
};
