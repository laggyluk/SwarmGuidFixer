// Copyright Epic Games, Inc. All Rights Reserved.

#include "GuidFixer.h"
#include "GuidFixerStyle.h"
#include "GuidFixerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName GuidFixerTabName("GuidFixer");

#define LOCTEXT_NAMESPACE "FGuidFixerModule"

void FGuidFixerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGuidFixerStyle::Initialize();
	FGuidFixerStyle::ReloadTextures();

	FGuidFixerCommands::Register();
	
	FixMaterialGuidsCommands = MakeShareable(new FUICommandList);

	FixMaterialGuidsCommands->MapAction(
		FGuidFixerCommands::Get().FixMaterialGuids,
		FExecuteAction::CreateRaw(this, &FGuidFixerModule::FixMaterialGuids),
		FCanExecuteAction());
	
	FixTextureGuidsCommands = MakeShareable(new FUICommandList);

	FixTextureGuidsCommands->MapAction(
		FGuidFixerCommands::Get().FixTextureGuids,
		FExecuteAction::CreateRaw(this, &FGuidFixerModule::FixTextureGuids),
		FCanExecuteAction());
	

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGuidFixerModule::RegisterMenus));
}

void FGuidFixerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGuidFixerStyle::Shutdown();

	FGuidFixerCommands::Unregister();
}

void FGuidFixerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
	{
		FToolMenuSection& Section = Menu->AddSection("GuidFixer", LOCTEXT("GUID Fixer", "GUID Fixer"));
		Section.AddMenuEntryWithCommandList(FGuidFixerCommands::Get().FixMaterialGuids, FixMaterialGuidsCommands);
		Section.AddMenuEntryWithCommandList(FGuidFixerCommands::Get().FixTextureGuids, FixTextureGuidsCommands);
	}
}

// This function is a modified version of laggyluk's SwarmGuidFixer
// https://github.com/laggyluk/SwarmGuidFixer
void FGuidFixerModule::FixMaterialGuids()
{
	TMap<FGuid, UMaterialInterface*> Guids;

	bool bMadeChanges = false;
	for (TObjectIterator<UMaterialInterface> Material; Material; ++Material)
	{
		if (!Material->GetLightingGuid().IsValid())
		{
			continue;
		}
		
		UMaterialInterface** Result = Guids.Find(Material->GetLightingGuid());

		if (Result == nullptr)
		{
			Guids.Add(Material->GetLightingGuid(), *Material);
		}
		else
		{
			Material->SetLightingGuid();
			Material->Modify();
			bMadeChanges = true;
			UE_LOG(LogTemp, Display, TEXT("%s: Material has had its GUID updated."), *Material->GetName());
		}
	}
	
	const FText DialogText = FText::FromString(bMadeChanges
			? "At least one material GUID has been changed. Use save all to save these changes."
			: "No duplicate material GUIDs found.");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FGuidFixerModule::FixTextureGuids()
{
	TMap<FGuid, UTexture*> Guids;

	bool bMadeChanges = false;
	for (TObjectIterator<UTexture> Texture; Texture; ++Texture)
	{
		if (!Texture->GetLightingGuid().IsValid())
		{
			continue;
		}
	
		UTexture** Result = Guids.Find(Texture->GetLightingGuid());
		if (Result == nullptr)
		{
			Guids.Add(Texture->GetLightingGuid(), *Texture);
		}
		else
		{
			Texture->SetLightingGuid();
			Texture->Modify();
			bMadeChanges = true;
			UE_LOG(LogTemp, Display, TEXT("%s: Texture has had its GUID updated."), *Texture->GetName());
		}
	}
	
	const FText DialogText = FText::FromString(bMadeChanges
			? "At least one texture GUID has been changed. Use save all to save these changes."
			: "No duplicate texture GUIDs found.");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGuidFixerModule, GuidFixer)