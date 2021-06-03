// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SOGGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Interface/PlayerControllerInterface.h"

ASOGGameMode::ASOGGameMode()
{
	CurrentNeededItemType = EQuestItemType::EQIT_None;

	QuestInfo.CurrentCount = 0;
	QuestInfo.NeededCount = 5;

	DelayBeforeMatchRestart = 10.f;

	GameRoundDuration = 60.f;
	CurrentRoundTime = 0.f;
}

void ASOGGameMode::BeginPlay()
{
	QuestInfo.NeededItem = GetRandomQuestItemType();

	SetGameRoundTimer();
}

bool ASOGGameMode::TryScore_Implementation(EQuestItemType ItemType) 
{
	if (ItemType == QuestInfo.NeededItem)
	{
		IncrementScore();

		return true;
	}

	return false;
}

void ASOGGameMode::IncrementScore()
{
	++QuestInfo.CurrentCount;

	UpdateQuestInfoOnClients();

	if (QuestInfo.CurrentCount == QuestInfo.NeededCount)
	{
		EndGameMatch(true);
	}
}

EQuestItemType ASOGGameMode::GetRandomQuestItemType() const
{
	EQuestItemType Type = (EQuestItemType)FMath::RandRange(1, (uint8)EQuestItemType::EQIT_MAX - 1);

	return Type;
}

void ASOGGameMode::UpdateQuestInfoOnClients()
{
	auto ControllerIter = GetWorld()->GetPlayerControllerIterator();
	for (ControllerIter; ControllerIter; ++ControllerIter)
	{
		IPlayerControllerInterface::Execute_UpdateQuestInfo(ControllerIter->Get(), QuestInfo);
	}
}

void ASOGGameMode::UpdateQuestInfoForClient_Implementation(APlayerController* Player)
{
	IPlayerControllerInterface::Execute_UpdateQuestInfo(Player, QuestInfo);
}

void ASOGGameMode::EndGameMatch(bool IsVictory)
{

	FTimerHandle RestartTimer;

	GetWorld()->GetTimerManager().SetTimer(RestartTimer, this, &ASOGGameMode::RestartMatch, 0.1f, 
											false, DelayBeforeMatchRestart);

	EndMatchMessage(IsVictory, DelayBeforeMatchRestart);
}

void ASOGGameMode::RestartMatch()
{
	GetWorld()->ServerTravel(GetWorld()->GetMapName(), true);
}

void ASOGGameMode::EndMatchMessage(bool IsVictory, float DelayBeforeRestart)
{
	auto ControllerIter = GetWorld()->GetPlayerControllerIterator();
	for (ControllerIter; ControllerIter; ++ControllerIter)
	{
		IPlayerControllerInterface::Execute_UpdateMatchResultInfo(ControllerIter->Get(), 
														IsVictory, DelayBeforeRestart);
	}
}

void ASOGGameMode::SetGameRoundTimer()
{
	GetWorld()->GetTimerManager().SetTimer(GameRoundTimer, this, &ASOGGameMode::UpdateGameRoundTime, 1.f, true);

}

void ASOGGameMode::UpdateGameRoundTime()
{
	bool bQuestFailed = QuestInfo.CurrentCount != QuestInfo.NeededCount;
	bool bIsTimeOut = ++CurrentRoundTime == GameRoundDuration;
	if (bQuestFailed && bIsTimeOut)
	{
		EndGameMatch(false);
	}
}


float ASOGGameMode::GetRoundRemainingTime_Implementation()
{
	float RemainingTime = GameRoundDuration - CurrentRoundTime;
	RemainingTime -= 1.f; // For network latency compensation
	return  RemainingTime;
}