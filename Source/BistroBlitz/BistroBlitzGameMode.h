// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/steam_api.h"
#pragma warning(pop)

#define RAW_APP_ID "2629050"

#include "BistroBlitzGameMode.generated.h"

UCLASS(minimalapi)
class ABistroBlitzGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Destroyed();

public:
	ABistroBlitzGameMode();
	static constexpr const char* const APP_ID = RAW_APP_ID;
	CSteamID MyId;
};



