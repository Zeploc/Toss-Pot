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
	
	OriginalXSocketOffset = CameraBoom->SocketOffset.X;
}

// Called every frame
void ACameraMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Player1 && Player2)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector CenterPosition = FMath::Lerp(Player1->GetActorLocation(), Player2->GetActorLocation(), 0.5);
		//CurrentLocation.X = CenterPosition.X;
		//SetActorLocation(CurrentLocation);

		FVector Difference = Player1->GetActorLocation() - Player2->GetActorLocation();
		float Distance = Difference.Size();
		

		float CenterThreshold = 500.0f;
		float CenterOffsetThreshold = 200.0f;
		float MoveSpeed = 5.0f;
		float CenterMoveSpeed = 30.0f;
		FVector NewAimPos = CurrentLocation;

		FVector DifferenceNoZ = Difference;
		DifferenceNoZ.Z = 0;
		// If the players start spreading far away  //OR Camera center is too far from the center of players
		if (DifferenceNoZ.Size() > CenterThreshold)
		{
			NewAimPos.X = CenterPosition.X;
		}
		else if (abs(CenterPosition.X - CurrentLocation.X) > CenterOffsetThreshold)
		{
			NewAimPos.X = FMath::Lerp(CurrentLocation.X, CenterPosition.X, CenterMoveSpeed * DeltaTime);
		}

		
		NewAimPos.Y = CenterPosition.Y;


		// ### Finding zoom and boom arm offset ###
		float CurrentZoom = CameraBoom->TargetArmLength;
		float ScaleOutRatio = 0.4f;
		float GoalZoom = CloseBoomArmLength;
		float ZoomSpeed = 5.0f;

		float ZoomDistanceThresholdX = 1500.0f;
		float ZoomDistanceThresholdY = 1000.0f;
		float YExtra = 0.0f;
		if (abs(Difference.X) > ZoomDistanceThresholdX)
		{
			GoalZoom += abs(ZoomDistanceThresholdX - Distance) * ScaleOutRatio;
		}
		else if (abs(Difference.Y) > ZoomDistanceThresholdY)
		{
			GoalZoom += abs(ZoomDistanceThresholdY - Distance) * ScaleOutRatio;
			// CAUSES SLIGHT JOLT FROM BEING 0 to THIS VALUE, (REDUCE MINIMUM WITH THIS VALUE WOULD FIX IT
			YExtra = abs(ZoomDistanceThresholdY - Distance) * ScaleOutRatio;
		}

		// ### Z Height ###

		/*FVector ZDifference = Difference;
		ZDifference.X = 0;
		ZDifference.Y = 0;
		if (ZDifference.Size() > CenterThreshold)
		{
			NewAimPos.Z = CenterPosition.Z;
		}
		else if (abs(CenterPosition.Z - CurrentLocation.Z) > CenterOffsetThreshold)
		{
			NewAimPos.Z = FMath::Lerp(CurrentLocation.Z, CenterPosition.Z, CenterMoveSpeed * DeltaTime);
		}*/


		// ### SetZoom and boom offset ###
		
		CurrentZoom = FMath::Lerp(CurrentZoom, GoalZoom, ZoomSpeed * DeltaTime);
		CameraBoom->TargetArmLength = CurrentZoom;

		CurrentZoom += CloseBoomArmZ - CloseBoomArmLength;
		FVector NewSocketOffset = CameraBoom->SocketOffset;
		NewSocketOffset.Z = CurrentZoom;
		//float CurrentXExtra = OriginalXSocketOffset - NewSocketOffset.X;
		
		NewSocketOffset.X = FMath::Lerp(NewSocketOffset.X, OriginalXSocketOffset - YExtra, ZoomSpeed * DeltaTime);
		CameraBoom->SocketOffset = NewSocketOffset;

		// ### Set location ###
		CurrentLocation = FMath::Lerp(CurrentLocation, NewAimPos, MoveSpeed * DeltaTime);
		SetActorLocation(CurrentLocation);








		// Zoom  - CameraBoom->TargetArmLength, CloseBoomArmZ, CloseBoomArmLength
		// Center pos - CameraBoom->SocketOffset;
		// Center pos also? - SetActorLocation(CurrentPos);


		// Check player y distance is too far
		// OR
		// One player is outside pos range

		//bool bTooFarY = Distance.Y > DistanceMaxY;
		//bool bTooFarX = Distance.X > CenterThreshold;
		//bool bYHigherOffset = CenterPosition.Y > MaxPosY;
		//bool bYLowerOffset = CenterPosition.Y < MinPosY;

		//if (bTooFarY || bTooFarX || (bYHigherOffset || bYLowerOffset)) // or if players are too high or low
		//{
		//	float YDifference = Distance.Y - DistanceMaxY;
		//	float XDifference = Distance.X - CenterThreshold;
		//	float CurrentZoom = 0;
		//	if (bTooFarX && bTooFarY)
		//		CurrentZoom = XDifference + YDifference;
		//	else if (bTooFarX)
		//		CurrentZoom = XDifference;
		//	else if (bTooFarY)
		//		CurrentZoom = YDifference;



		//	if (bYHigherOffset || bYLowerOffset)
		//	{
		//		FVector CurrentPos = GetActorLocation();
		//		if (bYHigherOffset)
		//		{
		//			CurrentPos.Y = CenterPosition.Y - MaxPosY;
		//		}
		//		else
		//		{
		//			CurrentPos.Y = CenterPosition.Y - MinPosY;
		//		}
		//		SetActorLocation(CurrentPos);
		//		
		//	}

		//	
		//	float ratio = 0.4f;
		//	CurrentZoom *= ratio;
		//	CurrentZoom += CloseBoomArmLength;
		//	CameraBoom->TargetArmLength = CurrentZoom;
		//	CurrentZoom += CloseBoomArmZ - CloseBoomArmLength;
		//	FVector NewSocketOffset = CameraBoom->SocketOffset;
		//	NewSocketOffset.Z = CurrentZoom;
		//	CameraBoom->SocketOffset = NewSocketOffset;
		//	

		//}
		////GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Orange, TEXT("Curren arm length " + FString::SanitizeFloat(CameraBoom->TargetArmLength)));

		//FVector CurrentPos = GetActorLocation();

		//CurrentPos.Z = (Player2->GetActorLocation() + Difference / 2).Z + ZHeight;
		//SetActorLocation(CurrentPos);
	}	
}

void ACameraMovement::SetControllersView()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this);
	UGameplayStatics::GetPlayerController(GetWorld(), 1)->SetViewTargetWithBlend(this);
}


