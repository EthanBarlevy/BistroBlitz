// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class BISTROBLITZ_API UWidgetBase : public UUserWidget
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

	UFUNCTION()
	void JoinOnClicked();
};
