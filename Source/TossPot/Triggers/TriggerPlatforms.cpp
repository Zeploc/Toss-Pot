// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerPlatforms.h"

#include "Engine.h"

ATriggerPlatforms::ATriggerPlatforms()
{

}

void ATriggerPlatforms::BeginPlay()
{
	Super::BeginPlay();
	if (Platform1)
	{
		StartPostion1 = Platform1->GetActorLocation();
	}
	if (Platform2)
	{
		StartPostion2 = Platform2->GetActorLocation();
	}
}

void ATriggerPlatforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Platform1 && bPlatform1Move)
	{
		FVector Direction = (EndPostion1 - StartPostion1);
		Direction.Normalize();
		FVector CurrentPlatformLocation = Platform1->GetActorLocation();


		if (bPlatform1DirectionForward)
		{
			Platform1->SetActorLocation(CurrentPlatformLocation + Direction * DeltaTime * Platform1Speed);

			FVector DirectionFromCurrent = EndPostion1 - CurrentPlatformLocation;
			DirectionFromCurrent.Normalize(); 
			FVector ResultVector = Direction + DirectionFromCurrent;
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Current Result: " + ResultVector.ToString() + " Vectors (Current | Direction) " + DirectionFromCurrent.ToCompactString() + " | " + Direction.ToCompactString()));
			if (ResultVector.GetAbs() == FVector::ZeroVector)
			{
				bPlatform1Move = false;
				Platform1->SetActorLocation(EndPostion1);
			}
		}
		else
		{
			Platform1->SetActorLocation(CurrentPlatformLocation - Direction * DeltaTime * Platform1Speed);

			FVector DirectionFromCurrent = StartPostion1 - CurrentPlatformLocation;
			DirectionFromCurrent.Normalize();
			FVector ResultVector = -Direction + DirectionFromCurrent;
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Current Result: " + ResultVector.ToString() + " Vectors (Current | Direction) " + DirectionFromCurrent.ToCompactString() + " | " + Direction.ToCompactString()));
			if (ResultVector.GetAbs() == FVector::ZeroVector)
			{
				bPlatform1Move = false;
				Platform1->SetActorLocation(StartPostion1);
			}
		}
	}

	if (Platform2 && bPlatform2Move)
	{
		FVector Direction = (EndPostion2 - StartPostion2);
		Direction.Normalize();
		FVector CurrentPlatformLocation = Platform2->GetActorLocation();
		
		if (bPlatform1DirectionForward)
		{
			Platform2->SetActorLocation(CurrentPlatformLocation + Direction * DeltaTime * Platform2Speed);

			FVector DirectionFromCurrent = EndPostion2 - CurrentPlatformLocation;
			DirectionFromCurrent.Normalize();
			FVector ResultVector = Direction + DirectionFromCurrent;
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Current Result: " + ResultVector.ToString() + " Vectors (Current | Direction) " + DirectionFromCurrent.ToCompactString() + " | " + Direction.ToCompactString()));
			if (ResultVector.GetAbs() == FVector::ZeroVector)
			{
				bPlatform2Move = false;
				Platform2->SetActorLocation(EndPostion2);
			}
		}
		else
		{
			Platform2->SetActorLocation(CurrentPlatformLocation - Direction * DeltaTime * Platform2Speed);

			FVector DirectionFromCurrent = StartPostion2 - CurrentPlatformLocation;
			DirectionFromCurrent.Normalize();
			FVector ResultVector = -Direction + DirectionFromCurrent;
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Current Result: " + ResultVector.ToString() + " Vectors (Current | Direction) " + DirectionFromCurrent.ToCompactString() + " | " + Direction.ToCompactString()));
			if (ResultVector.GetAbs() == FVector::ZeroVector)
			{
				bPlatform2Move = false;
				Platform2->SetActorLocation(StartPostion2);
			}
		}
	}
}

void ATriggerPlatforms::Trigger()
{
	bPlatform1DirectionForward = !bPlatform1DirectionForward;
	bPlatform2DirectionForward = !bPlatform2DirectionForward;
	bPlatform1Move = true;
	bPlatform2Move = true;
}

void ATriggerPlatforms::DisableTrigger()
{
	bPlatform1DirectionForward = false;
	bPlatform2DirectionForward = false;
	bPlatform1Move = true;
	bPlatform2Move = true;
}
