// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GuidFixerCommands.h"

#define LOCTEXT_NAMESPACE "FGuidFixerModule"

void FGuidFixerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GuidFixer", "Execute GuidFixer action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
