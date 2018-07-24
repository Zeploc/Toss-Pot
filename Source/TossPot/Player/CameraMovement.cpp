// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"

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
	if (Player1 && Player2)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector CenterPosition = FMath::Lerp(Player1->GetActorLocation(), Player2->GetActorLocation(), 0.5);
		CurrentLocation.X = CenterPosition.X;
		SetActorLocation(CurrentLocation);

		FVector Distance = (Player1->GetActorLocation() - Player2->GetActorLocation()).GetAbs();
		

		// Check player y distance is too far
		// OR
		// One player is outside pos range
		float CenterThreshold = 1000.0f;

		bool bTooFarY = Distance.Y > DistanceMaxY;
		bool bTooFarX = Distance.X > CenterThreshold;
		bool bYHigherOffset = CenterPosition.Y > MaxPosY;
		bool bYLowerOffset = CenterPosition.Y < MinPosY;

		if (bTooFarY || bTooFarX || (bYHigherOffset || bYLowerOffset)) // or if players and too high or low
		{
			float YDifference = Distance.Y - DistanceMaxY;
			float XDifference = Distance.X - CenterThreshold;
			float CurrentZoom = 0;
			if (bTooFarX && bTooFarY)
				CurrentZoom = XDifference + YDifference;
			else if (bTooFarX)
				CurrentZoom = XDifference;
			else if (bTooFarY)
				CurrentZoom = YDifference;


			
			if (bYHigherOffset || bYLowerOffset)
			{
				FVector CurrentPos = GetActorLocation();
				if (bYHigherOffset)
				{
					CurrentPos.Y = CenterPosition.Y - MaxPosY;
				}
				else
				{
					CurrentPos.Y = CenterPosition.Y - MinPosY;
				}
				SetActorLocation(CurrentPos);
				
			}
			
			float ratio = 0.4f;
			CurrentZoom *= ratio;
			CurrentZoom += CloseBoomArmLength;
			CameraBoom->TargetArmLength = CurrentZoom;
			CurrentZoom += CloseBoomArmZ - CloseBoomArmLength;
			FVector NewSocketOffset = CameraBoom->SocketOffset;
			NewSocketOffset.Z = CurrentZoom;
			CameraBoom->SocketOffset = NewSocketOffset;
			

		}
		GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Orange, TEXT("Curren arm length " + FString::SanitizeFloat(CameraBoom->TargetArmLength)));

	}	
}


