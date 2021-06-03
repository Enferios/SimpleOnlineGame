// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Pickups/MasterPickup.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

#include "Interface/GameModeInterface.h"

// Sets default values
AMasterPickup::AMasterPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	Type = EQuestItemType::EQIT_None;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(GetRootComponent());
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupMesh->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	PickupInteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	PickupInteractCollision->SetupAttachment(PickupMesh);
	PickupInteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupInteractCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	PickupInteractCollision->InitSphereRadius(30.f);
}

// Called when the game starts or when spawned
void AMasterPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterPickup::Interact_Implementation(AActor* Interactor)
{
	auto GameMode = UGameplayStatics::GetGameMode(this);
	bool bSuccessfullyPickupOperation = IGameModeInterface::Execute_TryScore(GameMode, Type);

	if (bSuccessfullyPickupOperation)
	{
		SetLifeSpan(0.1f);
	}
}

