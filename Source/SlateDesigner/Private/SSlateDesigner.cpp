// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlateDesigner.h"

#include "SlateDesignerStyle.h"
#include "SlateOptMacros.h"
#include "SSlateCodeEditor.h"
#include "SSlateView.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SlateDesignerSpace"

static const FName SlateViewName = "SlateView";
static const FName SlateTextName = "SlateText";

void SSlateDesigner::Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& MajorDock, const TSharedPtr<SWindow>& MajorWindow)
{
	SlateCodeEditor = SNew(SSlateCodeEditor);
	
	SlateView = SNew(SSlateView, SlateCodeEditor);
	
	TabManager = FGlobalTabmanager::Get()->NewTabManager(MajorDock);
	TSharedRef<FWorkspaceItem> SlateDesignerMenuGroup = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("SlateDesignerGroup", "Slate Desinger"));

	TabManager->RegisterTabSpawner(SlateViewName, FOnSpawnTab::CreateRaw(this, &SSlateDesigner::OnSpawnSlateViewTab))
		.SetGroup(SlateDesignerMenuGroup)
		.SetDisplayName(LOCTEXT("SlateViewName", "Slate View"));

	TabManager->RegisterTabSpawner(SlateTextName, FOnSpawnTab::CreateRaw(this, &SSlateDesigner::OnSpawnSlateEditorTab))
		.SetGroup(SlateDesignerMenuGroup)
		.SetDisplayName(LOCTEXT("SlateTextName", "Slate Text"));


	const TSharedRef<FTabManager::FLayout> Layout = TabManager->NewLayout("SlateDesignerLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(SlateViewName, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(SlateTextName, ETabState::OpenedTab)
			)
		);

	ChildSlot
	[
		TabManager->RestoreFrom(Layout, MajorWindow).ToSharedRef()
	];
}

TSharedRef<SDockTab> SSlateDesigner::OnSpawnSlateViewTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> DockTab = SNew(SDockTab).TabRole(NomadTab)
		.OnCanCloseTab_Lambda([](){return false;})
		[
			SlateView.ToSharedRef()
		];

	return DockTab;
}

TSharedRef<SDockTab> SSlateDesigner::OnSpawnSlateEditorTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> DockTab = SNew(SDockTab).TabRole(NomadTab)
		.OnCanCloseTab_Lambda([](){return false;})
		[
			SlateCodeEditor.ToSharedRef()
		];

	return DockTab;
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
