// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"
#include "Components/Button.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/steam_api.h"
#pragma warning(pop)

void UWidgetBase::NativeConstruct()
{
	if (SearchForLobby)
	{
		SearchForLobby->OnClicked.AddDynamic(this, &UWidgetBase::SearchOnClicked);
	}

	if (JoinLobby)
	{
		JoinLobby->OnClicked.AddDynamic(this, &UWidgetBase::JoinOnClicked);
	}
}

void UWidgetBase::SearchOnClicked()
{
	SteamAPICall_t CreateLobby(k_ELobbyTypePrivate);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OwO"));
}

void UWidgetBase::JoinOnClicked()
{

}

