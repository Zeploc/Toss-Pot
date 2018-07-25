// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TossPotGameMode.h"

#include "TossPotCharacter.h"
#include "Engine.h"

ATossPotGameMode::ATossPotGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATossPotGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ATossPotGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player1 && Player2)
	{
		FVector Difference = Player1->GetActorLocation() - Player2->GetActorLocation();
		Difference.Z = 0; // Only Horizontal
		float Distance = Difference.Size();
		if (Distance > SafeRange)
		{
			if (Distance > DeadZone)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Red, TEXT("DEADZONE " + FString::SanitizeFloat(Distance)));
				CurrentDanger = 0.0f;
			}
			else
			{
				float CurrentValue = (Distance - SafeRange) / (DeadZone - SafeRange);
				CurrentDanger = 1 - CurrentValue;
				//GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Orange, TEXT("UNSAFE " + FString::SanitizeFloat(CurrentValue)));
			}
		}
		else if (CurrentDanger != 1.0f)
			CurrentDanger = 1.0f;
	}
}
