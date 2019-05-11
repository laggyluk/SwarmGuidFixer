// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SwarmGuidFixerStyle.h"

class FSwarmGuidFixerCommands : public TCommands<FSwarmGuidFixerCommands>
{
public:

	FSwarmGuidFixerCommands()
		: TCommands<FSwarmGuidFixerCommands>(TEXT("SwarmGuidFixer"), NSLOCTEXT("Contexts", "SwarmGuidFixer", "SwarmGuidFixer Plugin"), NAME_None, FSwarmGuidFixerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
