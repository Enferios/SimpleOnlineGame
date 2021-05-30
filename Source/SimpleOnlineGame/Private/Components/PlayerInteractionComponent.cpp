// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerInteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "TimerManager.h"

#include "Interface/InteractableInterface.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Tracing
	TraceInterval = 0.1f;
	TraceDistance = 1000.f;
}
// Called when the game starts
void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();

	StartTracing();
}


// Called every frame
void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerInteractionComponent::Init()
{
	PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

void UPlayerInteractionComponent::SetTarget(AActor* NewTarget) 
{
	if (CurrentTarget == NewTarget)
	{
		return;
	}

	ClearTarget();

	CurrentTarget = NewTarget;
	IInteractableInterface::Execute_StartFocus(CurrentTarget);
	OnTargetChanged.Broadcast(CurrentTarget);
}

void UPlayerInteractionComponent::ClearTarget()
{
	if (CurrentTarget != nullptr)
	{
		IInteractableInterface::Execute_EndFocus(CurrentTarget);
	}

	CurrentTarget = nullptr;
}

bool UPlayerInteractionComponent::CheckTarget(AActor* Target)
{
	return Target->Implements<UInteractableInterface>();
}

void UPlayerInteractionComponent::StartTracing()
{
	GetWorld()->GetTimerManager().SetTimer(TraceTimer, this, &UPlayerInteractionComponent::TraceForInteract, TraceInterval, true);
}

void UPlayerInteractionComponent::StopTracing()
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimer);
}

void UPlayerInteractionComponent::TraceForInteract()
{
	FHitResult HitResult;
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + (PlayerCamera->GetForwardVector() * TraceDistance);
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		if (CheckTarget(HitResult.GetActor()))
		{
			SetTarget(HitResult.GetActor());
		}
	}
	else
	{
		ClearTarget();
		OnTargetChanged.Broadcast(CurrentTarget);
	}
}