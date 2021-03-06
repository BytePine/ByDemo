// Copyright Byteyang Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FByMotionControllerPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
};
