// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Interface/GameModeInterface.h"

#include "SOGGameMode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SIMPLEONLINEGAME_API ASOGGameMode : public AGameMode,
	public IGameModeInterface
{
	GENERATED_BODY()
	
public:

	ASOGGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode|Quest")
	EQuestItemType CurrentNeededItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode|Quest")
	int32 CurrentScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode|Quest")
	int32 NeededScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	float DelayBeforeMatchRestart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	float GameRoundDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	float CurrentRoundTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode|Quest")
	FQuestInfo QuestInfo;

public:

	/** Called when the player tries to interact with pickup actor */
	bool TryScore(EQuestItemType ItemType);
	bool TryScore_Implementation(EQuestItemType ItemType);

	void UpdateQuestInfoForClient(APlayerController* Player);
	void UpdateQuestInfoForClient_Implementation(APlayerController* Player);

	float GetRoundRemainingTime();
	float GetRoundRemainingTime_Implementation();

protected:

	void BeginPlay() override;

	/** Quest */
	void IncrementScore();
	EQuestItemType GetRandomQuestItemType() const;
	void UpdateQuestInfoOnClients();
	
	

	void EndMatchMessage(bool IsVictory, float DelayBeforeRestart);

	void EndGameMatch(bool IsVictory);

	void RestartMatch();

private:

	void SetGameRoundTimer();
	void UpdateGameRoundTime();
	void StartGameRoundTimerOnClients();

private:

	FTimerHandle GameRoundTimer;
};
