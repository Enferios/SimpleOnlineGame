// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interface/InteractableInterface.h"
#include "Data/DataTypes.h"

#include "MasterPickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS(Abstract)
class SIMPLEONLINEGAME_API AMasterPickup : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	EQuestItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	USphereComponent* PickupInteractCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* Interactor);
	virtual void Interact_Implementation(AActor* Interactor);

};
