// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MayaBridge.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "MayaBridgeStyle.h"
#include "MayaBridgeCommands.h"

#include "LevelEditor.h"

static const FName MayaBridgeTabName("MayaBridge");

#define LOCTEXT_NAMESPACE "FMayaBridgeModule"

void FMayaBridgeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMayaBridgeStyle::Initialize();
	FMayaBridgeStyle::ReloadTextures();

	FMayaBridgeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMayaBridgeCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMayaBridgeModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMayaBridgeModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMayaBridgeModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FMayaBridgeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMayaBridgeStyle::Shutdown();

	FMayaBridgeCommands::Unregister();
}

void FMayaBridgeModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FMayaBridgeModule::PluginButtonClicked()")),
							FText::FromString(TEXT("MayaBridge.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FMayaBridgeModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMayaBridgeCommands::Get().PluginAction);
}

void FMayaBridgeModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMayaBridgeCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMayaBridgeModule, MayaBridge)