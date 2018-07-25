// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerPlatforms.h"

#include "Engine.h"
#include "Components/AudioComponent.h"

ATriggerPlatforms::ATriggerPlatforms()
{
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform 1"));
	Platform->SetCollisionObjectType(ECC_GameTraceChannel2);

	MovementAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MovementAudioComponent"));
	MovementAudioComponent->SetSound(MovingSound);
}

void ATriggerPlatforms::BeginPlay()
{
	Super::BeginPlay();
	StartPostion1 = GetActorLocation();
	if (Platform2)
	{
		StartPostion2 = Platform2->GetActorLocation();
	}
}

void ATriggerPlatforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bPlatform1Move)
	{
		FVector Direction = (EndPostion1 - StartPostion1);
		Direction.Normalize();
		FVector CurrentPlatformLocation = GetActorLocation();


		if (bPlatform1DirectionForward)
		{
			SetActorLocation(CurrentPlatformLocation + Direction * DeltaTime * Platform1Speed, true);
			
			FVector DirectionFromCurrent = EndPostion1 - CurrentPlatformLocation;
			DirectionFromCurrent.Normalize(); 
			FVector ResultVector = Direction + DirectionFromCurrent;
			MovementAudioComponent->Play();
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Current Result: " + ResultVector.ToString() + " Vectors (Current | Direction) " + DirectionFromCurrent.ToCompactString() + " | " + Direction.ToCompactString()));
			if (ResultVector.GetAbs() == FVector::ZeroVector)
			{
				bPlatform1Move = false;
				SetActorLocation(EndPostion1);
				MovementAudioComponent->Stop();
			}
		}
		else
		{
			SetActorLocation(CurrentPlatformLocation - Direction * DeltaTime * Platform1Speed, true);

			FVector DirectionFromCurrent = StartPostion1 - CurrentPlatformLocation;
			DirectionFromCurrent.Normalize();
			FVector ResultVector = -Direction + DirectionFromCurrent;
			//UGameplayStatics::PlaySoundAtLocation(this, MovingSound, GetActorLocation());
			MovementAudioComponent->Play();
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Current Result: " + ResultVector.ToString() + " Vectors (Current | Direction) " + DirectionFromCurrent.ToCompactString() + " | " + Direction.ToCompactString()));
			if (ResultVector.GetAbs() == FVector::ZeroVector)
			{
				bPlatform1Move = false;
				SetActorLocation(StartPostion1);
				MovementAudioComponent->Stop();
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
			Platform2->SetActorLocation(CurrentPlatformLocation + Direction * DeltaTime * Platform2Speed, true);

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
			Platform2->SetActorLocation(CurrentPlatformLocation - Direction * DeltaTime * Platform2Speed, true);

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
