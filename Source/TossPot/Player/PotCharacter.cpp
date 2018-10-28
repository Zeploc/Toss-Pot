// Fill out your copyright notice in the Description page of Project Settings.

#include "PotCharacter.h"
#include "Engine.h"
#include "Particles/ParticleSystemComponent.h"

APotCharacter::APotCharacter()
{
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	 
	ParticleSystem->SetupAttachment(RootComponent);
}

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
	if (CanJump()) UGameplayStatics::PlaySound2D(this, JumpSound);
	Jump();
	
	CurrentlyJumping = true;
}

void APotCharacter::PotStopJump()
{
	StopJumping();
}

