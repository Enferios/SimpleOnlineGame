// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Spawn/MasterPickupSpawner.h"

#include "GameplayMechanics/Pickups/MasterPickup.h"

// Sets default values
AMasterPickupSpawner::AMasterPickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;

}

// Called when the game starts or when spawned
void AMasterPickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPickup();
}


TSubclassOf<AMasterPickup> AMasterPickupSpawner::GetRandomPickupClass() const
{
	int32 MaxIndex = PickupClassesToSpawn.Num() - 1 ;

	int32 RandIndex = FMath::RandRange(0, MaxIndex);

	return PickupClassesToSpawn.Array()[RandIndex];
}

void AMasterPickupSpawner::SpawnPickup()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (PickupClassesToSpawn.Num() > 0)
		{
			auto Pickup = GetRandomPickupClass();

			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation{ 0.f };
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<AMasterPickup>(Pickup, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
	

}

