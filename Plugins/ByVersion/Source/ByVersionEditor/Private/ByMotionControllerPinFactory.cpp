// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "ByMotionControllerPinFactory.h"
#include "MotionControllerComponent.h"

#include "SGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_VariableSet.h"
#include "MotionControllerComponent.h"
#include "ByMotionSourceWidget.h"
#include "ScopedTransaction.h"

class SByMotionControllerSourceGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SByMotionControllerSourceGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		return	SNew(SByMotionSourceWidget)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.OnMotionSourceChanged(this, &SByMotionControllerSourceGraphPin::OnMotionSourceChanged)
			.OnGetMotionSourceText(this, &SByMotionControllerSourceGraphPin::GetMotionSourceValueText);
	}
	//~ End SGraphPin Interface

	private:

	void OnMotionSourceChanged(FName NewMotionSource)
	{
		FString NewMotionSourceString = NewMotionSource.ToString();

		if (!GraphPinObj->GetDefaultAsString().Equals(NewMotionSourceString))
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeMotionSourcePinValue", "Change Motion Source Pin Value"));
			GraphPinObj->Modify();

			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, NewMotionSourceString);
		}
	}

	FText GetMotionSourceValueText() const
	{
		return FText::FromString(GraphPinObj->GetDefaultAsString());
	}

};

TSharedPtr<SGraphPin> FByMotionControllerPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Name)
	{
		if (UK2Node_VariableSet* Setter = Cast<UK2Node_VariableSet>(InPin->GetOuter()))
		{
			if (Setter->GetVariableSourceClass() == UMotionControllerComponent::StaticClass() && Setter->GetVarName() == GET_MEMBER_NAME_CHECKED(UMotionControllerComponent, MotionSource))
			{
				return SNew(SByMotionControllerSourceGraphPin, InPin);
			}
		}
	}

	return nullptr;
}
