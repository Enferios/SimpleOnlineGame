// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Interface/PlayerControllerInterface.h"

#include "SOGPlayerController.generated.h"

class UGameOverlay;

UCLASS(Abstract)
class SIMPLEONLINEGAME_API ASOGPlayerController : public APlayerController,
	public IPlayerControllerInterface
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "PlayerController|HUD")
	TSubclassOf<UGameOverlay> GameOverlayWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "PlayerController|HUD")
	UGameOverlay* OverlayWidget;

public:

	/** Called from game mode */
	void UpdateQuestInfo(const FQuestInfo& QuestInfo);
	void UpdateQuestInfo_Implementation(const FQuestInfo& QuestInfo);

	/** Called from game mode */
	void UpdateMatchResultInfo(bool IsVictory, float DelayBeforeRestart);
	void UpdateMatchResultInfo_Implementation(bool IsVictory, float DelayBeforeRestart);
	
protected:

	void BeginPlay() override;

private:

	void InitOverlayWidget();

	UFUNCTION(Client, Reliable, Category = "Player Controller|Info")
	void Client_UpdateHUDQuestInfo(FQuestInfo QuestInfo);

	UFUNCTION(Server, Reliable, Category = "Player Controller")
	void Server_UpdateQuestInfoRequest();

	UFUNCTION(Client, Reliable, Category = "Player Controller|Info")
	void Client_UpdateMatchResultInfo(bool IsVictory, float DelayBeforeRestart);

	UFUNCTION(Client, Reliable, Category = "Player Controller|Info")
	void Client_StartGameRoundTimer(float RoundDuration);

	UFUNCTION(Server, Reliable, Category = "Player Controller")
	void Server_GetRoundRemainingTime();
};
