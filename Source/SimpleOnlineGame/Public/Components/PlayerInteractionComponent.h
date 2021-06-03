// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLEONLINEGAME_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChanged, AActor*, NewTarget);

public:	
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

	float TraceInterval;
	float TraceDistance;

	FOnTargetChanged OnTargetChanged;

	FTimerHandle TraceTimer;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	AActor* CurrentTarget;

	UCameraComponent* PlayerCamera;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartTracing();
	void StopTracing();

private:

	void Init();

	void SetTarget(AActor* NewTarget);
	void ClearTarget();
	bool CheckTarget(AActor* Target);

	void TraceForInteract();
		
};
