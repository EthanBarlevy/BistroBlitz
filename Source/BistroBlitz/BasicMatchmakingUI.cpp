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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ButtonClicked"));
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
	m_CallResultLobbyMatchList.Set(hSteamAPICall, this, &UBasicMatchmakingUI::OnLobbyMatchList);
}

void UBasicMatchmakingUI::OnLobbyMatchList(LobbyMatchList_t *pLobbyMatchList, bool bIOFailure)
{
	auto numLobbies = pLobbyMatchList->m_nLobbiesMatching;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("lobbies: %f"), numLobbies));
	if (pLobbyMatchList->m_nLobbiesMatching <= 0)
	{
		SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic, 2);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("LobbyCreated"));
	}
	else
	{
		for (uint64 i = 0; i < numLobbies; i++)
		{
			CSteamID LobbyID = SteamMatchmaking()->GetLobbyByIndex(i);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("lobbyIndex: %f"), 500));
			//SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(LobbyID);
		}
	}
}

void UBasicMatchmakingUI::JoinOnClicked()
{

}
