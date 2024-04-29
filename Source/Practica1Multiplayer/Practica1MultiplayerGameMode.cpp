// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica1MultiplayerGameMode.h"
#include "Practica1MultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APractica1MultiplayerGameMode::APractica1MultiplayerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
