// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterPickupSpawner.generated.h"

class AMasterPickup;

UCLASS(Abstract)
class SIMPLEONLINEGAME_API AMasterPickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterPickupSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickupSpawner|Spawn")
	TSet<TSubclassOf<AMasterPickup>> PickupClassesToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


private:

	TSubclassOf<AMasterPickup> GetRandomPickupClass() const;

	void SpawnPickup();

};
