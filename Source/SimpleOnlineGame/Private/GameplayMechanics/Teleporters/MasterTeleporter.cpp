// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Teleporters/MasterTeleporter.h"

#include "Components/BoxComponent.h"

// Sets default values
AMasterTeleporter::AMasterTeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	TeleporterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleporterMesh"));
	TeleporterMesh->SetupAttachment(GetRootComponent());

	TeleporterInteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	TeleporterInteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TeleporterInteractCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	TeleporterInteractCollision->SetupAttachment(TeleporterMesh);

	SpawnPoint = GetActorLocation();

}

// Called when the game starts or when spawned
void AMasterTeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterTeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterTeleporter::Interact_Implementation(AActor* Interactor)
{
	Teleport(Interactor);
}

void AMasterTeleporter::Teleport(AActor* Target)
{
	if (DestinationTeleporter != nullptr)
	{
		Target->SetActorLocation(DestinationTeleporter->GetSpawnLocation(), false, nullptr, ETeleportType::ResetPhysics);
	}
}

const FVector AMasterTeleporter::GetSpawnLocation()
{
	return GetActorLocation() + SpawnPoint;
}