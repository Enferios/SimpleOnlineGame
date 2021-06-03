// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SOGPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "HUD/GameOverlay.h"
#include "GameMode/SOGGameMode.h"
#include "Interface/GameModeInterface.h"

void ASOGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() != ROLE_Authority)
	{
		InitOverlayWidget();
	}

}

void ASOGPlayerController::UpdateQuestInfo_Implementation(const FQuestInfo& QuestInfo)
{
    Client_UpdateHUDQuestInfo(QuestInfo);
}

void ASOGPlayerController::Client_UpdateHUDQuestInfo_Implementation(FQuestInfo QuestInfo)
{
	if (OverlayWidget)
	{
		OverlayWidget->UpdateQuestInfo(QuestInfo);
	}
}

void ASOGPlayerController::InitOverlayWidget()
{
	if (GameOverlayWidgetClass != nullptr)
	{
		OverlayWidget = CreateWidget<UGameOverlay>(this, GameOverlayWidgetClass);

		if (OverlayWidget)
		{
			Server_UpdateQuestInfoRequest();

			Server_GetRoundRemainingTime();

			OverlayWidget->AddToViewport();
		}
	}
}

void ASOGPlayerController::Server_UpdateQuestInfoRequest_Implementation()
{
	auto GameMode = UGameplayStatics::GetGameMode(this);
	IGameModeInterface::Execute_UpdateQuestInfoForClient(GameMode, this);
}

void ASOGPlayerController::Client_UpdateMatchResultInfo_Implementation(bool IsVictory, float DelayBeforeRestart)
{
	if (OverlayWidget)
	{
		OverlayWidget->UpdateEndMatchInfo(IsVictory, DelayBeforeRestart);
	}
}

void ASOGPlayerController::UpdateMatchResultInfo_Implementation(bool IsVictory, float DelayBeforeRestart)
{
	Client_UpdateMatchResultInfo(IsVictory, DelayBeforeRestart);
}

void ASOGPlayerController::StartGameRoundTimer_Implementation(float RoundDuration)
{
	Client_StartGameRoundTimer(RoundDuration);
}

void ASOGPlayerController::Client_StartGameRoundTimer_Implementation(float RoundDuration)
{
	if (OverlayWidget)
	{
		OverlayWidget->StartRoundTimer(RoundDuration);
	}
}

void ASOGPlayerController::Server_GetRoundRemainingTime_Implementation()
{
	auto GameMode = UGameplayStatics::GetGameMode(this);
	float CurrentRoundTime = IGameModeInterface::Execute_GetRoundRemainingTime(GameMode);

	Client_StartGameRoundTimer(CurrentRoundTime);
}