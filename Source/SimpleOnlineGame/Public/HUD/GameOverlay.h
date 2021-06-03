// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Data/DataTypes.h"

#include "GameOverlay.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SIMPLEONLINEGAME_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Overlay|Quest")
	void UpdateQuestInfo(FQuestInfo QuestInfo);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Overlay|Quest")
	void UpdateEndMatchInfo(bool IsVictory, float DelayBeforeRestart);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Overlay")
	void StartRoundTimer(float RoundDuration);
};
