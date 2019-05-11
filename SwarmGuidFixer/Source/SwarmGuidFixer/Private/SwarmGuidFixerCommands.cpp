// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SwarmGuidFixerCommands.h"

#define LOCTEXT_NAMESPACE "FSwarmGuidFixerModule"

void FSwarmGuidFixerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "SwarmGuidFixer", "Execute SwarmGuidFixer action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
