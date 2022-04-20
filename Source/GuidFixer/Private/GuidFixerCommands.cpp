// Copyright Epic Games, Inc. All Rights Reserved.

#include "GuidFixerCommands.h"

#define LOCTEXT_NAMESPACE "FGuidFixerModule"

void FGuidFixerCommands::RegisterCommands()
{
	UI_COMMAND(FixMaterialGuids, "Fix Material GUIDs",
	           "Fixes material GUIDs so that there are no materials with duplicate IDs.",
	           EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(FixTextureGuids, "Fix Texture GUIDs",
	           "Fixes texture GUIDs so that there are no textures with duplicate IDs.",
	           EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(FixEmptyTextureGuids, "Fix Empty Texture GUIDs",
	           "This will update empty texture GUIDs, which may help if the other fixes weren't enough to solve the issue.\n"
	           "This will attempt to update engine textures, so will often report making changes that will be reset on restart.",
	           EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
