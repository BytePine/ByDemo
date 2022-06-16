// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyCustomizationHelpers.h"
/**
 * 
 */
class SByPropertyEditorAsset : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SByPropertyEditorAsset)
		: _DisplayThumbnail(true)
		, _DisplayUseSelected(true)
		, _DisplayBrowse(true)
		, _EnableContentPicker(true)
		, _DisplayCompactSize(true)
		, _ThumbnailPool(nullptr)
		, _ThumbnailSize(FIntPoint(48, 48))
		, _ObjectPath()
		, _Class(nullptr)
		, _CustomContentSlot()
		{}
		SLATE_ARGUMENT(TOptional<bool>, AllowClear)
		SLATE_ARGUMENT(bool, DisplayThumbnail)
		SLATE_ARGUMENT(bool, DisplayUseSelected)
		SLATE_ARGUMENT(bool, DisplayBrowse)
		SLATE_ARGUMENT(bool, EnableContentPicker)
		SLATE_ARGUMENT(bool, DisplayCompactSize)
		SLATE_ARGUMENT(TSharedPtr<FAssetThumbnailPool>, ThumbnailPool)
		SLATE_ARGUMENT(FIntPoint, ThumbnailSize)
		SLATE_ATTRIBUTE(FString, ObjectPath)
		SLATE_ARGUMENT(UClass*, Class)
		SLATE_ARGUMENT(TOptional<TArray<UFactory*>>, NewAssetFactories)
		SLATE_EVENT(FOnSetObject, OnSetObject)
		SLATE_EVENT(FOnShouldFilterAsset, OnShouldFilterAsset)
		SLATE_NAMED_SLOT(FArguments, CustomContentSlot)
		SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle)
		SLATE_ARGUMENT(TArray<FAssetData>, OwnerAssetDataArray)

	SLATE_END_ARGS()
};
