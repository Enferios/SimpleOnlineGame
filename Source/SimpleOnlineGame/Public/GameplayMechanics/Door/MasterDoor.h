// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interface/InteractableInterface.h"

#include "MasterDoor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS(Abstract)
class SIMPLEONLINEGAME_API AMasterDoor : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterDoor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	UBoxComponent* DoorInteractCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void Interact(AActor* Interactor);
	virtual void Interact_Implementation(AActor* Interactor);

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Door")
	void OpenDoor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Door")
	void CloseDoor();
};
