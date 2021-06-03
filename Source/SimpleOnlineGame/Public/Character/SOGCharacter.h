// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SOGCharacter.generated.h"

class UCameraComponent;
class UPlayerInteractionComponent;

UCLASS(Abstract)
class SIMPLEONLINEGAME_API ASOGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASOGCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Movement")
	bool bCanMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	float TurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	float LookUpRate;

	UPROPERTY(VisibleAnywhere, Category = "Character|Camera")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Character|Interaction")
	UPlayerInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Character|Interaction")
	AActor* CurrentTarget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**Camera rotation */
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	/** Movement input */
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	/** Interaction */
	void Interact();

	UFUNCTION(Server, Reliable, Category = "Interaction")
	void Server_Interact();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool CanMove();

	UFUNCTION()
	void UpdateCurrentTarget(AActor* NewTarget);

};
