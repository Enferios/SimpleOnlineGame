// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interface/InteractableInterface.h"

#include "MasterTeleporter.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SIMPLEONLINEGAME_API AMasterTeleporter : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterTeleporter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	AMasterTeleporter* DestinationTeleporter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	UStaticMeshComponent* TeleporterMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Teleport")
	UBoxComponent* TeleporterInteractCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true), Category = "Teleport")
	FVector SpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* Interactor);
	void Interact_Implementation(AActor* Interactor);

private:

	void Teleport(AActor* Target);

	const FVector GetSpawnLocation();

};
