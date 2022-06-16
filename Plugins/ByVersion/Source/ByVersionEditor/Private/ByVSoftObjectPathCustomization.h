﻿// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class IPropertyHandle;

/**
 * 
 */
class BYVERSIONEDITOR_API FByVSoftObjectPathCustomization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() 
    {
        return MakeShareable( new FByVSoftObjectPathCustomization );
    }
    
    /** IPropertyTypeCustomization interface */
    virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;
    virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;
    
private:
    /** Handle to the struct property being customized */
    TSharedPtr<IPropertyHandle> StructPropertyHandle;
};
