// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GuidFixer.h"
#include "GuidFixerStyle.h"
#include "GuidFixerCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"

static const FName GuidFixerTabName("GuidFixer");

#define LOCTEXT_NAMESPACE "FGuidFixerModule"

void FGuidFixerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGuidFixerStyle::Initialize();
	FGuidFixerStyle::ReloadTextures();

	FGuidFixerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGuidFixerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FGuidFixerModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FGuidFixerModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FGuidFixerModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FGuidFixerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FGuidFixerStyle::Shutdown();

	FGuidFixerCommands::Unregister();
}

void FGuidFixerModule::PluginButtonClicked()
{
	/*
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FGuidFixerModule::PluginButtonClicked()")),
							FText::FromString(TEXT("GuidFixer.cpp"))
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

void FGuidFixerModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FGuidFixerCommands::Get().PluginAction);
}

void FGuidFixerModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FGuidFixerCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGuidFixerModule, GuidFixer)