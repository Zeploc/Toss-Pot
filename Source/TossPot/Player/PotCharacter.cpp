// Fill out your copyright notice in the Description page of Project Settings.

#include "PotCharacter.h"
#include "Engine.h"


void APotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentlyJumping && CanJump())
		CurrentlyJumping = false;
}

// Input
void APotCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APotCharacter::PotJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APotCharacter::PotStopJump);
}

void APotCharacter::PotJump()
{
	Jump();
	UGameplayStatics::PlaySound2D(this, JumpSound);

	CurrentlyJumping = true;
}

void APotCharacter::PotStopJump()
{
	StopJumping();
}

