// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "ByMotionSourceWidget.h"
#include "PropertyHandle.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Features/IModularFeatures.h"
#include "IMotionController.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SEditableTextBox.h"

void SByMotionSourceWidget::Construct(const FArguments& InArgs)
{
	check(InArgs._OnMotionSourceChanged.IsBound());
	check(InArgs._OnGetMotionSourceText.IsBound());

	OnMotionSourceChanged = InArgs._OnMotionSourceChanged;
	OnGetMotionSourceText = InArgs._OnGetMotionSourceText;

	this->ChildSlot
	[
		SNew(SComboButton)
		.ContentPadding(1)
		.OnGetMenuContent(this, &SByMotionSourceWidget::BuildMotionSourceMenu)
		.ButtonContent()
		[
			SNew(SEditableTextBox)
			.RevertTextOnEscape(true)
			.SelectAllTextWhenFocused(true)
			.Text(this, &SByMotionSourceWidget::GetMotionSourceText)
			.OnTextCommitted(this, &SByMotionSourceWidget::OnMotionSourceValueTextComitted)
		]
	];
}

TSharedRef<SWidget> SByMotionSourceWidget::BuildMotionSourceMenu()
{
	TMap<FName, TArray<FName>> CategorizedMotionSources;

	TArray<IMotionController*> MotionControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	for (IMotionController* MotionController : MotionControllers)
	{
		if (MotionController)
		{
			TArray<FMotionControllerSource> MotionSources;
			MotionController->EnumerateSources(MotionSources);

			for (FMotionControllerSource& Source : MotionSources)
			{
				CategorizedMotionSources.FindOrAdd(Source.EditorCategory).AddUnique(Source.SourceName);
			}
		}
	}

	FMenuBuilder MenuBuilder(true, NULL);

	for (TPair<FName, TArray<FName>> Pair : CategorizedMotionSources)
	{
		const bool bWrapInSection = !Pair.Key.IsNone();
		if (bWrapInSection)
		{
			MenuBuilder.BeginSection(Pair.Key, FText::FromName(Pair.Key));
		}

		for (FName SourceName : Pair.Value)
		{
			FUIAction MenuAction(FExecuteAction::CreateSP(this, &SByMotionSourceWidget::OnMotionSourceComboValueCommited, SourceName));
			MenuBuilder.AddMenuEntry(FText::FromName(SourceName), FText(), FSlateIcon(), MenuAction);
		}

		if (bWrapInSection)
		{
			MenuBuilder.EndSection();
		}
	}

	return MenuBuilder.MakeWidget();
}

FText SByMotionSourceWidget::GetMotionSourceText() const
{
	return OnGetMotionSourceText.Execute();
}

void SByMotionSourceWidget::OnMotionSourceValueTextComitted(const FText& InNewText, ETextCommit::Type InTextCommit)
{
	FName NewMotionSource = *InNewText.ToString();
	OnMotionSourceChanged.Execute(NewMotionSource);
}

void SByMotionSourceWidget::OnMotionSourceComboValueCommited(FName InMotionSource)
{
	FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::Cleared);
	OnMotionSourceChanged.Execute(InMotionSource);
}
