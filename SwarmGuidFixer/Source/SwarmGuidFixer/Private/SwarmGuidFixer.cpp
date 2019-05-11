// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SwarmGuidFixer.h"
#include "SwarmGuidFixerStyle.h"
#include "SwarmGuidFixerCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"

static const FName SwarmGuidFixerTabName("SwarmGuidFixer");

#define LOCTEXT_NAMESPACE "FSwarmGuidFixerModule"

void FSwarmGuidFixerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSwarmGuidFixerStyle::Initialize();
	FSwarmGuidFixerStyle::ReloadTextures();

	FSwarmGuidFixerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSwarmGuidFixerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSwarmGuidFixerModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSwarmGuidFixerModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSwarmGuidFixerModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FSwarmGuidFixerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSwarmGuidFixerStyle::Shutdown();

	FSwarmGuidFixerCommands::Unregister();
}

void FSwarmGuidFixerModule::PluginButtonClicked()
{
	/*
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FSwarmGuidFixerModule::PluginButtonClicked()")),
							FText::FromString(TEXT("SwarmGuidFixer.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	*/
	TMap<FGuid, UMaterialInterface*> guids;

	for (TObjectIterator<UMaterialInterface> it; it; ++it)
	{
		UMaterialInterface** result = guids.Find(it->GetLightingGuid());

		if (result == nullptr)
		{
			guids.Add(it->GetLightingGuid(), *it);
		}
		else
		{
			it->SetLightingGuid();
			it->Modify();
		}
	}
	FText DialogText = FText::FromString("Done, save all to save all");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FSwarmGuidFixerModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSwarmGuidFixerCommands::Get().PluginAction);
}

void FSwarmGuidFixerModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSwarmGuidFixerCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSwarmGuidFixerModule, SwarmGuidFixer)