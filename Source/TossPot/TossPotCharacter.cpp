// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TossPotCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"

#include "Interactables/InteractActor.h"

#include "DrawDebugHelpers.h"

ATossPotCharacter::ATossPotCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	/*GetCapsuleComponent()->DestroyComponent();
	SetRootComponent(GetMesh());*/

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input
void ATossPotCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATossPotCharacter::TossPotJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATossPotCharacter::TossPotStopJump);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATossPotCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ATossPotCharacter::MoveUp);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATossPotCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATossPotCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATossPotCharacter::Interact);
}

void ATossPotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentlyJumping && CanJump())
		CurrentlyJumping = false;
}

void ATossPotCharacter::TossPotJump()
{
	Jump();
	CurrentlyJumping = true;
}

void ATossPotCharacter::TossPotStopJump()
{
	StopJumping();
}

void ATossPotCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void ATossPotCharacter::MoveUp(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}

void ATossPotCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ATossPotCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ATossPotCharacter::Interact()
{
	FHitResult hit;
	FVector EndLocation = GetActorLocation() + GetActorRotation().Vector() * InteractRange;
	FCollisionQueryParams Traceparams(TEXT("Interact Trace"), false, this);

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), EndLocation, ECC_GameTraceChannel1, Traceparams);
	AInteractActor* InteractActor = Cast<AInteractActor>(hit.Actor);
	if (InteractActor)
	{
		InteractActor->Interact();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Interact with interact actor"));
	}
	else if (hit.bBlockingHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Interact Hit object " + hit.Actor.Get()->GetFName().ToString()));
	}
	
}