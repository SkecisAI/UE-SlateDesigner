// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlateCodeEditor.h"

#include "SlateDesignerStyle.h"
#include "SlateOptMacros.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlateCodeEditor::Construct(const FArguments& InArgs)
{
	SlateTextBox = SNew(SMultiLineEditableTextBox)
	.Font(SlateDesignerStyle::GetStyle()->GetFontStyle("SlateDesigner.SlateText"))
	.OnTextChanged(this, &SSlateCodeEditor::HandleSlateTextChanged);
	
	ChildSlot
	[
		// Populate the widget
		SlateTextBox.ToSharedRef()
	];
}

void SSlateCodeEditor::HandleSlateTextChanged(const FText& Text)
{
	if (OnSlateTextChanged.IsBound())
	{
		OnSlateTextChanged.Execute(Text);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
