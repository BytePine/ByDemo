// Copyright Epic Games, Inc. All Rights Reserved.

#include "ByVersionEditor.h"
#include "ByMotionControllerPinFactory.h"
#include "ByVSoftObjectPathCustomization.h"

#define LOCTEXT_NAMESPACE "FByVersionEditorModule"

void FByVersionEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	RegisterPropertyTypeCustomizations();
	RegisterObjectCustomizations();

	TSharedPtr<FByMotionControllerPinFactory> MotionControllerPinFactory = MakeShareable(new FByMotionControllerPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(MotionControllerPinFactory);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FByVersionEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

		// Unregister all classes customized by name
		for (auto It = RegisteredClassNames.CreateConstIterator(); It; ++It)
		{
			if (It->IsValid())
			{
				PropertyModule.UnregisterCustomClassLayout(*It);
			}
		}

		// Unregister all structures
		for (auto It = RegisteredPropertyTypes.CreateConstIterator(); It; ++It)
		{
			if(It->IsValid())
			{
				PropertyModule.UnregisterCustomPropertyTypeLayout(*It);
			}
		}
	
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

void FByVersionEditorModule::RegisterPropertyTypeCustomizations()
{
	RegisterCustomPropertyTypeLayout("ByVSoftObjectPath", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FByVSoftObjectPathCustomization::MakeInstance));
}

void FByVersionEditorModule::RegisterObjectCustomizations()
{
	
}

void FByVersionEditorModule::RegisterCustomClassLayout(FName ClassName,
	FOnGetDetailCustomizationInstance DetailLayoutDelegate)
{
	check(ClassName != NAME_None);

	RegisteredClassNames.Add(ClassName);

	static FName PropertyEditor("PropertyEditor");
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
	PropertyModule.RegisterCustomClassLayout( ClassName, DetailLayoutDelegate );
}

void FByVersionEditorModule::RegisterCustomPropertyTypeLayout(FName PropertyTypeName,
                                                              FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate)
{
	check(PropertyTypeName != NAME_None);

	RegisteredPropertyTypes.Add(PropertyTypeName);

	static FName PropertyEditor("PropertyEditor");
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
	PropertyModule.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FByVersionEditorModule, ByVersionEditor)