// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Data/DataTypes.h"

#include "PlayerControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEONLINEGAME_API IPlayerControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerControllerInterface")
	void UpdateQuestInfo(const FQuestInfo& QuestInfo);

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerControllerInterface")
	void UpdateMatchResultInfo(bool IsVictory, float DelayBeforeRestart);

	UFUNCTION(BlueprintNativeEvent, Category = "PlayerControllerInterface")
	void StartGameRoundTimer(float RoundDuration);
};
