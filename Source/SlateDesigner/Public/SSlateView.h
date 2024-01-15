// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Designer/SDesignerView.h"
#include "Widgets/SCompoundWidget.h"

class SSlateCodeEditor;
class SMultiLineEditableTextBox;


/**
 * 
 */
class SLATEDESIGNER_API SSlateView : public SDesignSurface
{
public:
	SLATE_BEGIN_ARGS(SSlateView)
		{
		}

	SLATE_END_ARGS()
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedPtr<SSlateCodeEditor> InSlateCodeEditor);

	void OnSlateCodeTextChanged(FText Text);
protected:
	virtual int32 GetSnapGridSize() const override;

	TSharedRef<SWidget> TranslateSlateRecursively(int& CurLineIndex);

private:
	TSharedPtr<SBox> PreviewWidgetBox;

	TSharedPtr<SSlateCodeEditor> SlateCodeEditor;

	TSharedPtr<SWidget> EmptyWidget;

	TArray<FString> SlateStringLines;
};
