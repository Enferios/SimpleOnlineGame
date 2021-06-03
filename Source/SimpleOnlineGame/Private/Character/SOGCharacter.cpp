// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SOGCharacter.h"

#include "Camera/CameraComponent.h"

#include "Components/PlayerInteractionComponent.h"
#include "Interface/InteractableInterface.h"

// Sets default values
ASOGCharacter::ASOGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;

	// Movement
	bCanMove = true;

	// Mouse
	TurnRate = 50.f;
	LookUpRate = 50.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));

}

// Called when the game starts or when spawned
void ASOGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionComponent->OnTargetChanged.AddDynamic(this, &ASOGCharacter::UpdateCurrentTarget);
}

// Called every frame
void ASOGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASOGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ASOGCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASOGCharacter::LookUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASOGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASOGCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ASOGCharacter::Interact);
}

void ASOGCharacter::Turn(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		float DeltaSeconds = GetWorld()->GetDeltaSeconds();
		float YawDelta = AxisValue * DeltaSeconds * TurnRate;

		AddControllerYawInput(YawDelta);
	}
}

void ASOGCharacter::LookUp(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		float DeltaSeconds = GetWorld()->GetDeltaSeconds();
		float PitchDelta = AxisValue * DeltaSeconds * LookUpRate;

		AddControllerPitchInput(PitchDelta);
	}
}

void ASOGCharacter::MoveForward(float AxisValue)
{
	if (AxisValue != 0.f && CanMove())
	{
		FRotator ControllerRotation = GetControlRotation();
		FRotator YawRotation = FRotator(0.f, ControllerRotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, AxisValue);
	}
}

void ASOGCharacter::MoveRight(float AxisValue)
{
	if (AxisValue != 0.f && CanMove())
	{
		FRotator ControllerRotation = GetControlRotation();
		FRotator YawRotation = FRotator(0.f, ControllerRotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, AxisValue);
	}
}
void ASOGCharacter::Interact()
{
	Server_Interact();
}

void ASOGCharacter::Server_Interact_Implementation()
{
	if (CurrentTarget != nullptr)
	{
		IInteractableInterface::Execute_Interact(CurrentTarget, this);
	}
}

bool ASOGCharacter::CanMove()
{
	return bCanMove;
}

void ASOGCharacter::UpdateCurrentTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
}