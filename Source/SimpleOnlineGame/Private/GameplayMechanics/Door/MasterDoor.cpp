// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Door/MasterDoor.h"

#include "Components/BoxComponent.h"

// Sets default values
AMasterDoor::AMasterDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());

	DoorInteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	DoorInteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DoorInteractCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	DoorInteractCollision->SetupAttachment(DoorMesh);
}

// Called when the game starts or when spawned
void AMasterDoor::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMasterDoor::Interact_Implementation(AActor* Interactor)
{
	OpenDoor();
}

void AMasterDoor::OpenDoor_Implementation()
{

}

void AMasterDoor::CloseDoor_Implementation()
{

}
