// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "ByPropertyCustomizationHelpers.h"

void SByObjectPropertyEntryBox::Construct(const FArguments& InArgs)
{
	ObjectPath = InArgs._ObjectPath;
	OnObjectChanged = InArgs._OnObjectChanged;
	OnShouldSetAsset = InArgs._OnShouldSetAsset;
	OnIsEnabled = InArgs._OnIsEnabled;

	const TArray<FAssetData>& OwnerAssetDataArray = InArgs._OwnerAssetDataArray;

	bool bDisplayThumbnail = InArgs._DisplayThumbnail;
	FIntPoint ThumbnailSize(48, 48);
	if (InArgs._ThumbnailSizeOverride.IsSet())
	{
		ThumbnailSize = InArgs._ThumbnailSizeOverride.Get();
	}

	if( InArgs._PropertyHandle.IsValid() && InArgs._PropertyHandle->IsValidHandle() )
	{
		PropertyHandle = InArgs._PropertyHandle;

		// check if the property metadata wants us to display a thumbnail
		const FString& DisplayThumbnailString = PropertyHandle->GetProperty()->GetMetaData(TEXT("DisplayThumbnail"));
		if(DisplayThumbnailString.Len() > 0)
		{
			bDisplayThumbnail = DisplayThumbnailString == TEXT("true");
		}

		// check if the property metadata has an override to the thumbnail size
		const FString& ThumbnailSizeString = PropertyHandle->GetProperty()->GetMetaData(TEXT("ThumbnailSize"));
		if ( ThumbnailSizeString.Len() > 0 )
		{
			FVector2D ParsedVector;
			if ( ParsedVector.InitFromString(ThumbnailSizeString) )
			{
				ThumbnailSize.X = (int32)ParsedVector.X;
				ThumbnailSize.Y = (int32)ParsedVector.Y;
			}
		}

		// if being used with an object property, check the allowed class is valid for the property
		FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(PropertyHandle->GetProperty());
		if (ObjectProperty != NULL)
		{
			checkSlow(InArgs._AllowedClass->IsChildOf(ObjectProperty->PropertyClass));
		}
	}

	ChildSlot
	[	
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.FillWidth(1)
		.VAlign(VAlign_Center)	
		[
			SAssignNew(PropertyEditorAsset, SByPropertyEditorAsset)
				.ObjectPath( this, &SByObjectPropertyEntryBox::OnGetObjectPath )
				.Class( InArgs._AllowedClass )
				.NewAssetFactories( InArgs._NewAssetFactories )
				.IsEnabled(this, &SByObjectPropertyEntryBox::IsEnabled)
				.OnSetObject(this, &SByObjectPropertyEntryBox::OnSetObject)
				.ThumbnailPool(InArgs._ThumbnailPool)
				.DisplayThumbnail(bDisplayThumbnail)
				.OnShouldFilterAsset(InArgs._OnShouldFilterAsset)
				.AllowClear(InArgs._AllowClear)
				.DisplayUseSelected(InArgs._DisplayUseSelected)
				.DisplayBrowse(InArgs._DisplayBrowse)
				.EnableContentPicker(InArgs._EnableContentPicker)
				.PropertyHandle(PropertyHandle)
				.OwnerAssetDataArray(OwnerAssetDataArray)
				.ThumbnailSize(ThumbnailSize)
				.DisplayCompactSize(InArgs._DisplayCompactSize)
				.CustomContentSlot()
				[
					InArgs._CustomContentSlot.Widget
				]
		]
	];
}

void SByObjectPropertyEntryBox::GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth)
{
	checkf(PropertyEditorAsset.IsValid(), TEXT("SObjectPropertyEntryBox hasn't been constructed yet."));
	// PropertyEditorAsset->GetDesiredWidth(OutMinDesiredWidth, OutMaxDesiredWidth);
}

void SByObjectPropertyEntryBox::OnSetObject(const FAssetData& AssetData)
{
	if( PropertyHandle.IsValid() && PropertyHandle->IsValidHandle() )
	{
		if (!OnShouldSetAsset.IsBound() || OnShouldSetAsset.Execute(AssetData))
		{
			PropertyHandle->SetValue(AssetData);
		}
	}
	OnObjectChanged.ExecuteIfBound(AssetData);
}

FString SByObjectPropertyEntryBox::OnGetObjectPath() const
{
	FString StringReference;
	if (ObjectPath.IsSet())
	{
		StringReference = ObjectPath.Get();
	}
	else if( PropertyHandle.IsValid() )
	{
		PropertyHandle->GetValueAsFormattedString( StringReference );
	}
	
	return StringReference;
}

bool SByObjectPropertyEntryBox::IsEnabled() const
{
	bool IsEnabled = true;
	if (PropertyHandle.IsValid())
	{
		IsEnabled &= PropertyHandle->IsEditable();
	}

	if (OnIsEnabled.IsBound())
	{
		IsEnabled &= OnIsEnabled.Execute();
	}

	return IsEnabled;
}
