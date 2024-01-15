// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateDesigner.h"

#include "SlateDesignerStyle.h"
#include "SSlateDesigner.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FSlateDesignerModule"

void FSlateDesignerModule::StartupModule()
{
	SlateDesignerStyle::Initilize();
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		FName("SlateDesignerTab"),
		FOnSpawnTab::CreateRaw(this, &FSlateDesignerModule::SpawnSlateDesignerTab))
		.SetDisplayName(LOCTEXT("SlateDesignerTab", "SlateDesigner"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetToolsCategory());
	
}

void FSlateDesignerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("SlateDesignerTab"));
	SlateDesignerStyle::Shutdown();
}

TSharedRef<SDockTab> FSlateDesignerModule::SpawnSlateDesignerTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedPtr<SDockTab> DockTab = SNew(SDockTab).TabRole(NomadTab);
	TSharedPtr<SWidget> TabContent = SNew(SSlateDesigner, DockTab.ToSharedRef(), SpawnTabArgs.GetOwnerWindow());

	DockTab->SetContent(TabContent.ToSharedRef());

	return DockTab.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateDesignerModule, SlateDesigner)