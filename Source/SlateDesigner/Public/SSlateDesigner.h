// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SSlateCodeEditor;
class SSlateView;
class SMultiLineEditableTextBox;
/**
 * 
 */
class SLATEDESIGNER_API SSlateDesigner : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlateDesigner)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& MajorDock, const TSharedPtr<SWindow>& MajorWindow);

	TSharedRef<SDockTab> OnSpawnSlateViewTab(const FSpawnTabArgs& SpawnTabArgs);

	TSharedRef<SDockTab> OnSpawnSlateEditorTab(const FSpawnTabArgs& SpawnTabArgs);

private:

	TSharedPtr<FTabManager> TabManager;

	TSharedPtr<SSlateView> SlateView;

	TSharedPtr<SSlateCodeEditor> SlateCodeEditor;
};
