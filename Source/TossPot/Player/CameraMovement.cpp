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
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(-40.f, 0.f, 180.f);
	//CameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));

	// Create a camera and attach to boom
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(RootComponent);
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
}

// Called when the game starts or when spawned
void ACameraMovement::BeginPlay()
{
	Super::BeginPlay();
	
	//OriginalXSocketOffset = CameraBoom->SocketOffset.X;
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

		float CenterThreshold = 400.0f;
		float CenterOffsetThreshold = 200.0f;
		float MoveSpeed = 6.0f;
		float CenterMoveSpeed = 30.0f;
		float CenterOffsetMoveSpeed = 20.0f;
		FVector NewAimPos = CurrentLocation;

		float ExtraNeeded = 0.0f;
		FVector FurtherPlayer = Player1->GetActorLocation();
		if (abs((Player2->GetActorLocation() - CurrentLocation).X) > abs((FurtherPlayer - CurrentLocation).X) + ExtraNeeded)
		{
			FurtherPlayer = Player2->GetActorLocation();
		}
		FVector Direction = (FurtherPlayer - CurrentLocation);
		Direction.Normalize();

		// If the players start spreading far away  //OR Camera center is too far from the center of players
		if (abs(Difference.X) >= CenterThreshold)
		{
			NewAimPos.X = FMath::Lerp(CurrentLocation.X, CenterPosition.X, CenterMoveSpeed * DeltaTime); //CenterPosition.X;
		}
		else if (abs(FurtherPlayer.X - CurrentLocation.X) > CenterOffsetThreshold)
		{

			FVector ExtraDistance = FurtherPlayer - (CurrentLocation + Direction * CenterOffsetThreshold);

			float NewXPosition = CurrentLocation.X + ExtraDistance.X;// (CenterPosition.X - CurrentLocation.X) - (Direction.X) * Distance / 4.0f; // (CurrentLocation + Direction * CenterOffsetThreshold).X; // CenterOffsetThreshold - -CurrentLocation.X;
			//NewXPosition += CenterOffsetThreshold - CenterPosition.X + CurrentLocation.X;
			NewAimPos.X = FMath::Lerp(CurrentLocation.X, NewXPosition, CenterOffsetMoveSpeed * DeltaTime);
		}

		
		NewAimPos.Y = CenterPosition.Y;


		// ### Finding zoom and boom arm offset ###
		float CurrentZoom = MainCamera->RelativeLocation.Size();// 0;// CameraBoom->TargetArmLength;
		float XScaleOutRatio = 0.5f;
		float YScaleOutRatio = 0.7f;
		float GoalZoom = CloseBoomArmLength;
		float ZoomSpeed = 5.0f;

		float ZoomDistanceThresholdX = 900.0f;
		float ZoomDistanceThresholdY = 700.0f;
		float YExtra = 0.0f;

		if (abs(Difference.X) > ZoomDistanceThresholdX)
		{
			GoalZoom += abs(ZoomDistanceThresholdX - Distance) * XScaleOutRatio;
		}
		else if (abs(Difference.Y) > ZoomDistanceThresholdY)
		{
			GoalZoom += abs(ZoomDistanceThresholdY - Distance) * YScaleOutRatio;
			// CAUSES SLIGHT JOLT FROM BEING 0 to THIS VALUE, (REDUCE MINIMUM WITH THIS VALUE WOULD FIX IT
			YExtra = abs(ZoomDistanceThresholdY - Distance) * YScaleOutRatio;
		}

		// ### Z Height ###

		float FarHeightDistance = 200.0f;
		float ZMinusCenterSize = 85.0f;
		
		if (abs(CenterPosition.Z - ZMinusCenterSize - CurrentLocation.Z) > FarHeightDistance || (CurrentLocation.Z > 0 && CenterPosition.Z - ZMinusCenterSize <= 10.0f))
		{
			NewAimPos.Z = FMath::Lerp(CurrentLocation.Z, CenterPosition.Z, CenterMoveSpeed * DeltaTime);
		}
		NewAimPos.Z = FMath::Lerp(CurrentLocation.Z, CenterPosition.Z - ZMinusCenterSize, CenterMoveSpeed * DeltaTime);


		float BackPlayerTooFarDistance = 100.0f;// 200.0f;
		float HeightZoomOutMultiplyer = 1.1f;
		float BackZoomOutMultiplyer = 1.1f;
		float HeightZOffset = 100.0f;
		
		FVector FurtherBackPlayer = Player1->GetActorLocation();
		if (Player2->GetActorLocation().Y < FurtherBackPlayer.Y)
			FurtherBackPlayer = Player2->GetActorLocation();
		
		if (abs(CurrentLocation.Z - FurtherBackPlayer.Z) > HeightZOffset)
		{
			if (abs(FurtherBackPlayer.Y - CurrentLocation.Y) > BackPlayerTooFarDistance)
			{
				GoalZoom -= (HeightZOffset - abs(CurrentLocation.Z - FurtherBackPlayer.Z)) * HeightZoomOutMultiplyer + (BackPlayerTooFarDistance - abs(FurtherBackPlayer.Y - CurrentLocation.Y)) * BackZoomOutMultiplyer;
			}
		}
		else
		{			
			//GoalZoom -= abs(OffFloorZOffset - CenterPosition.Z);
		}

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
		
		//CurrentZoom = FMath::Lerp(CurrentZoom, GoalZoom, ZoomSpeed * DeltaTime);
		//CameraBoom->TargetArmLength = CurrentZoom;

		///CurrentZoom += CloseBoomArmZ - CloseBoomArmLength;
		///FVector NewSocketOffset;// = 0 CameraBoom->SocketOffset;
		///NewSocketOffset.Z = CurrentZoom;
		//float CurrentXExtra = OriginalXSocketOffset - NewSocketOffset.X;
		
		//YExtra = FMath::Lerp(CameraBoom->SocketOffset.X - OriginalXSocketOffset, YExtra, ZoomSpeed * DeltaTime);

		///NewSocketOffset.X = FMath::Lerp(NewSocketOffset.X, OriginalXSocketOffset - YExtra, ZoomSpeed * DeltaTime);
		//CameraBoom->SocketOffset = NewSocketOffset;
		FVector DirectionFromCam = MainCamera->RelativeLocation;
		DirectionFromCam.Normalize();
		FVector NewCamLocation = FMath::Lerp(MainCamera->RelativeLocation, (DirectionFromCam) * GoalZoom, ZoomSpeed * DeltaTime);
		MainCamera->SetRelativeLocation(NewCamLocation);

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


