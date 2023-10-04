// Copyright Epic Games, Inc. All Rights Reserved.

#include "BistroBlitzGameMode.h"
#include "BistroBlitzCharacter.h"
#include "UObject/ConstructorHelpers.h"

void ABistroBlitzGameMode::BeginPlay()
{
	Super::BeginPlay();

	FFileHelper::SaveStringToFile(TEXT(RAW_APP_ID), TEXT("steam_appid.txt"));

	SteamAPI_RestartAppIfNecessary(atoi(APP_ID));

	if (SteamAPI_Init())
	{
		MyId = SteamUser()->GetSteamID();
	}
}

void ABistroBlitzGameMode::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Tick"));
	SteamAPI_RunCallbacks();
}

void ABistroBlitzGameMode::Destroyed()
{
	SteamAPI_Shutdown();
	Super::Destroyed();
}

ABistroBlitzGameMode::ABistroBlitzGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
