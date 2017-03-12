// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MayaBridge.h"
#include "MayaBridgeCommands.h"

#define LOCTEXT_NAMESPACE "FMayaBridgeModule"

void FMayaBridgeCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MayaBridge", "Execute MayaBridge action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
