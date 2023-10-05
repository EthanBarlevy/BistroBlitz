// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/steam_api.h"
#pragma warning(pop)

#include "BasicMatchmakingUI.generated.h"

/**
 * 
 */
UCLASS()
class BISTROBLITZ_API UBasicMatchmakingUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SearchForLobby;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* JoinLobby;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void SearchOnClicked();

	//UFUNCTION()
	void OnLobbyMatchList(LobbyMatchList_t *pLobbyMatchList, bool bIOFailure);

	UFUNCTION()
	void JoinOnClicked();

	void OnSearched(LobbyMatchList_t* pLobbyMatchList, bool bIOFailure);

	void OnEnterLobby(LobbyEnter_t* pLobbyEnter, bool bIOFailure);
};
