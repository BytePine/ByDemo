// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyCustomizationHelpers.h"
#include "ByPropertyEditorAsset.h"

/**
 * 
 */
class SByObjectPropertyEntryBox : public SCompoundWidget
{
 public:
	SLATE_BEGIN_ARGS( SByObjectPropertyEntryBox )
		: _AllowedClass( UObject::StaticClass() )
		, _AllowClear( true )
		, _DisplayUseSelected( true )
		, _DisplayBrowse( true )
		, _EnableContentPicker(true)
		, _DisplayCompactSize(false)
		, _DisplayThumbnail(true)
	{}
		/** The path to the object */
		SLATE_ATTRIBUTE( FString, ObjectPath )
		/** Optional property handle that can be used instead of the object path */
		SLATE_ARGUMENT( TSharedPtr<IPropertyHandle>, PropertyHandle )
		/** Optional, array of the objects path, in case the property handle is not valid we will use this one to pass additional object to the picker config*/
		SLATE_ARGUMENT(TArray<FAssetData>, OwnerAssetDataArray)
		/** Thumbnail pool */
		SLATE_ARGUMENT( TSharedPtr<FAssetThumbnailPool>, ThumbnailPool )
		/** Class that is allowed in the asset picker */
		SLATE_ARGUMENT( UClass*, AllowedClass )
		/** Optional list of factories which may be used to create new assets */
		SLATE_ARGUMENT( TOptional<TArray<UFactory*>>, NewAssetFactories )
		/** Called to check if an asset should be set */
		SLATE_EVENT(FOnShouldSetAsset, OnShouldSetAsset)
		/** Called when the object value changes */
		SLATE_EVENT(FOnSetObject, OnObjectChanged)
		/** Called to check if an asset is valid to use */
		SLATE_EVENT(FOnShouldFilterAsset, OnShouldFilterAsset)
		/** Called to check if the asset should be enabled. */
		SLATE_EVENT(FOnIsEnabled, OnIsEnabled)
		/** Whether the asset can be 'None' */
		SLATE_ARGUMENT(bool, AllowClear)
		/** Whether to show the 'Use Selected' button */
		SLATE_ARGUMENT(bool, DisplayUseSelected)
		/** Whether to show the 'Browse' button */
		SLATE_ARGUMENT(bool, DisplayBrowse)
		/** Whether to enable the content Picker */
		SLATE_ARGUMENT(bool, EnableContentPicker)
		/** Whether or not to display a smaller, compact size for the asset thumbnail */ 
		SLATE_ARGUMENT(bool, DisplayCompactSize)
		/** Whether or not to display the asset thumbnail */ 
		SLATE_ARGUMENT(bool, DisplayThumbnail)
		/** A custom content slot for widgets */ 
		SLATE_NAMED_SLOT(FArguments, CustomContentSlot)
		SLATE_ATTRIBUTE(FIntPoint, ThumbnailSizeOverride)
	SLATE_END_ARGS()

	BYVERSIONEDITOR_API void Construct( const FArguments& InArgs );

	BYVERSIONEDITOR_API void GetDesiredWidth(float& OutMinDesiredWidth, float &OutMaxDesiredWidth);

private:
	/**
	 * Delegate function called when an object is changed
	 */
	void OnSetObject(const FAssetData& InObject);

	/** @return the object path for the object we are viewing */
	FString OnGetObjectPath() const;

	bool IsEnabled() const;

private:
	/** Delegate to call to determine whether the asset should be set */
	FOnShouldSetAsset OnShouldSetAsset;
	/** Delegate to call when the object changes */
	FOnSetObject OnObjectChanged;
	/** Delegate to call to check if this widget should be enabled. */
	FOnIsEnabled OnIsEnabled;
	/** Path to the object */
	TAttribute<FString> ObjectPath;
	/** Handle to a property we modify (if any)*/
	TSharedPtr<IPropertyHandle> PropertyHandle;
	/** The widget used to edit the object 'property' */
	TSharedPtr<SByPropertyEditorAsset> PropertyEditorAsset;
};
