// Copyright Epic Games, Inc. All Rights Reserved.

#include "BistroBlitzGameMode.h"
#include "BistroBlitzCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABistroBlitzGameMode::ABistroBlitzGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
