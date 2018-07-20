// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "TossPotCharacter.h"


// Sets default values
ACameraMovement::ACameraMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(-40.f, 0.f, 180.f);
	CameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
}

// Called when the game starts or when spawned
void ACameraMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.X = FMath::Lerp(Player1->GetActorLocation(), Player2->GetActorLocation(), 0.5).X;
	SetActorLocation(CurrentLocation);

	FVector Distance = (Player1->GetActorLocation() - Player2->GetActorLocation()).GetAbs();

	float CenterThreshold = 1000.0f;
	if (Distance.X > CenterThreshold) // or if players and too high or low
	{
		float CurrentZoom = Distance.X - CenterThreshold;
		float ratio = 0.4f;
		CurrentZoom *= ratio;
		CurrentZoom += CloseBoomArmLength;
		CameraBoom->TargetArmLength = CurrentZoom;
		CurrentZoom += CloseBoomArmZ - CloseBoomArmLength;
		FVector NewSocketOffset = CameraBoom->SocketOffset;
		NewSocketOffset.Z = CurrentZoom;
		CameraBoom->SocketOffset = NewSocketOffset;
	}
}


