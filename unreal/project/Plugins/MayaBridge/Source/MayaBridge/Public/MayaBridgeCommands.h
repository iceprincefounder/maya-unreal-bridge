// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "MayaBridgeStyle.h"

class FMayaBridgeCommands : public TCommands<FMayaBridgeCommands>
{
public:

	FMayaBridgeCommands()
		: TCommands<FMayaBridgeCommands>(TEXT("MayaBridge"), NSLOCTEXT("Contexts", "MayaBridge", "MayaBridge Plugin"), NAME_None, FMayaBridgeStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
