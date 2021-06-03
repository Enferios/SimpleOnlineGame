// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DataTypes.generated.h"


UENUM(BlueprintType)
enum class EQuestItemType : uint8
{
    EQIT_None       UMETA(DisplayName = "None"),
    EQIT_Cube       UMETA(DisplayName = "Cube"),
    EQIT_Sphere     UMETA(DisplayName = "Sphere"),
    EQIT_Cone       UMETA(DisplayName = "Cone"),

    EQIT_MAX
};

USTRUCT(Blueprintable)
struct FQuestInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestItemType NeededItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NeededCount;
};