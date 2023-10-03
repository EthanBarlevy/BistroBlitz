// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMatchmakingUI.h"
#include "Components/Button.h"

void UBasicMatchmakingUI::NativeConstruct()
{
	if (SearchForLobby)
	{
		SearchForLobby->OnClicked.AddDynamic(this, &UBasicMatchmakingUI::SearchOnClicked);
	}

	if (JoinLobby)
	{
		JoinLobby->OnClicked.AddDynamic(this, &UBasicMatchmakingUI::JoinOnClicked);
	}
}

CCallResult <UBasicMatchmakingUI, LobbyMatchList_t> m_CallResultLobbyMatchList;
void UBasicMatchmakingUI::SearchOnClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ButtonClicked"));
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
	m_CallResultLobbyMatchList.Set(hSteamAPICall, this, &UBasicMatchmakingUI::OnLobbyMatchList);
}

void UBasicMatchmakingUI::OnLobbyMatchList(LobbyMatchList_t *pLobbyMatchList, bool bIOFailure)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("FoundLobbies"));
	//SteamAPICall_t CreateLobby(k_ELobbyTypePrivate);
}

void UBasicMatchmakingUI::JoinOnClicked()
{

}
