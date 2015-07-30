// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "JustDoIT.h"
#include "JustDoITGameMode.h"
#include "JustDoITHUD.h"
#include "JustDoITCharacter.h"

AJustDoITGameMode::AJustDoITGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/JustDoIT/Blueprints/BP_JustDoITCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


	// use our custom HUD class
	static ConstructorHelpers::FClassFinder<AHUD> HUDClassFinder(TEXT("/Game/JustDoIT/Blueprints/BP_JustDoITHUD"));
	HUDClass = HUDClassFinder.Class;
}
