// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnSlateTextChanged, FText);


class SMultiLineEditableTextBox;
/**
 * 
 */
class SLATEDESIGNER_API SSlateCodeEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlateCodeEditor)
		{
		}

	SLATE_END_ARGS()
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void HandleSlateTextChanged(const FText& Text);

	FOnSlateTextChanged OnSlateTextChanged;

private:
	TSharedPtr<SMultiLineEditableTextBox> SlateTextBox;
};
