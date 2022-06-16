// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "ByVSoftObjectPathCustomization.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EditorClassUtils.h"
#include "PropertyHandle.h"
#include "PropertyCustomizationHelpers.h"

void FByVSoftObjectPathCustomization::CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils )
{
	StructPropertyHandle = InStructPropertyHandle;
	
	const FString& MetaClassName = InStructPropertyHandle->GetMetaData("MetaClass");
	UClass* MetaClass = !MetaClassName.IsEmpty()
		? FEditorClassUtils::GetClassFromString(MetaClassName)
		: UObject::StaticClass();

	HeaderRow
	.NameContent()
	[
		InStructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(250.0f)
	.MaxDesiredWidth(0.0f)
	[
		// Add an object entry box.  Even though this isn't an object entry, we will simulate one
		SNew(SObjectPropertyEntryBox)
		.AllowedClass(MetaClass)
		.PropertyHandle(InStructPropertyHandle)
		.ThumbnailPool(StructCustomizationUtils.GetThumbnailPool())
	];

	// This avoids making duplicate reset boxes
	StructPropertyHandle->MarkResetToDefaultCustomized();
}

void FByVSoftObjectPathCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}