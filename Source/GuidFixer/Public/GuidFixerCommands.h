// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GuidFixerStyle.h"

class FGuidFixerCommands : public TCommands<FGuidFixerCommands>
{
public:

	FGuidFixerCommands()
		: TCommands<FGuidFixerCommands>(TEXT("GuidFixer"), NSLOCTEXT("Contexts", "GuidFixer", "GuidFixer Plugin"), NAME_None, FGuidFixerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
