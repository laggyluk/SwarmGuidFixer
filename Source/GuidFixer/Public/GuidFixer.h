// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FGuidFixerModule : public IModuleInterface
{
public:

	
	static FText Menu_FixTextureGuidsGetTitle();
	static FText Menu_FixMaterialGuidsGetTitle();
		
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void FixMaterialGuids();
	void FixTextureGuids();
	
	
private:
	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> FixMaterialGuidsCommands;
	TSharedPtr<class FUICommandList> FixTextureGuidsCommands;
};
