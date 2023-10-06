// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMatchmakingUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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

	if (StartGame)
	{
		StartGame->OnClicked.AddDynamic(this, &UBasicMatchmakingUI::StartGameOnClicked);
	}
}

CCallResult <UBasicMatchmakingUI, LobbyMatchList_t> m_CallResultLobbyMatchList;
void UBasicMatchmakingUI::SearchOnClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ButtonClicked"));
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
	m_CallResultLobbyMatchList.Set(hSteamAPICall, this, &UBasicMatchmakingUI::OnLobbyMatchList);
}

CCallResult <UBasicMatchmakingUI, LobbyDataUpdate_t> m_CallLobbyDataUpdate;
void UBasicMatchmakingUI::OnLobbyMatchList(LobbyMatchList_t *pLobbyMatchList, bool bIOFailure)
{
	auto numLobbies = pLobbyMatchList->m_nLobbiesMatching;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("lobbies: %f"), numLobbies));
	if (pLobbyMatchList->m_nLobbiesMatching <= 0)
	{
		SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic, 2);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("LobbyCreated"));
		m_CallLobbyDataUpdate.Set(hSteamAPICall, this, &UBasicMatchmakingUI::OnCreateLobby);
	}
	else
	{
		for (uint64 i = 0; i < numLobbies; i++)
		{
			LobbyID = SteamMatchmaking()->GetLobbyByIndex(i);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("lobbyIndex: %f"), 500));
			SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(LobbyID);
		}
	}
}

CCallResult <UBasicMatchmakingUI, LobbyMatchList_t> m_CallResultLobbyList;
void UBasicMatchmakingUI::JoinOnClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ButtonClicked"));
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
	m_CallResultLobbyList.Set(hSteamAPICall, this, &UBasicMatchmakingUI::OnSearched);
}

void UBasicMatchmakingUI::StartGameOnClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMap", true, "Listen");
	
}

void UBasicMatchmakingUI::JoinGameOnClicked()
{
	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//const char* data = SteamMatchmaking()->GetLobbyMemberData(LobbyID, SteamMatchmaking()->GetLobbyOwner(LobbyID), );
	PlayerController->ClientTravel("69.27.21.152:7777", ETravelType::TRAVEL_Absolute);
}

void UBasicMatchmakingUI::SetNumUsers()
{
	
}

CCallResult <UBasicMatchmakingUI, LobbyEnter_t> m_LobbyJoinEnter;
void UBasicMatchmakingUI::OnSearched(LobbyMatchList_t* pLobbyMatchList, bool bIOFailure)
{
	for (uint64 i = 0; i < pLobbyMatchList->m_nLobbiesMatching; i++)
	{
		LobbyID = SteamMatchmaking()->GetLobbyByIndex(i);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("lobbyIndex: %f"), 500));
		// will be changed to instead bring up a ui for browsing the servers availible
		SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(LobbyID);
		m_LobbyJoinEnter.Set(hSteamAPICall, this, &UBasicMatchmakingUI::OnEnterLobby);
	}
}

void UBasicMatchmakingUI::OnEnterLobby(LobbyEnter_t* pLobbyEnter, bool bIOFailure)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Joined"));
	NumUsers = SteamMatchmaking()->GetNumLobbyMembers(LobbyID);
}

void UBasicMatchmakingUI::OnCreateLobby(LobbyDataUpdate_t* pLobbyData, bool bIOFailure)
{
	LobbyID = pLobbyData->m_ulSteamIDLobby;
	NumUsers = SteamMatchmaking()->GetNumLobbyMembers(LobbyID);
	SteamMatchmaking()->SetLobbyMemberData(LobbyID, "Address", "");
}
