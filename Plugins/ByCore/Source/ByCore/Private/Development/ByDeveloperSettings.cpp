// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Development/ByDeveloperSettings.h"

UByDeveloperSettings* UByDeveloperSettings::Get()
{
	return GetMutableDefault<UByDeveloperSettings>();
}

FName UByDeveloperSettings::GetCategoryName() const
{
	return FName(TEXT("Plugins"));
}
