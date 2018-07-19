// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerPlatforms.h"

void ATriggerPlatforms::BeginPlay()
{
	StartPostion1 = Platform1->GetActorLocation();
	StartPostion2 = Platform2->GetActorLocation();
}

void ATriggerPlatforms::Tick(float DeltaTime)
{
	if (Platform1)
	{
		FVector Direction = (EndPostion1 - StartPostion1);
		Direction.Normalize();
		FVector CurrentPlatformLocation = Platform1->GetActorLocation();
		if (bPlatform1DirectionForward)
		{
			Platform1->SetActorLocation(CurrentPlatformLocation + Direction * DeltaTime);
		}
		else
		{
			Platform1->SetActorLocation(CurrentPlatformLocation + -Direction * DeltaTime);
		}
	}

	if (Platform2)
	{
		if (bPlatform2DirectionForward)
		{

		}
		else
		{

		}
	}
}

void ATriggerPlatforms::Trigger()
{
	bPlatform1DirectionForward = !bPlatform1DirectionForward;
	bPlatform2DirectionForward = !bPlatform2DirectionForward;
}

void ATriggerPlatforms::DisableTrigger()
{
	bPlatform1DirectionForward = false;
	bPlatform2DirectionForward = false;
}
