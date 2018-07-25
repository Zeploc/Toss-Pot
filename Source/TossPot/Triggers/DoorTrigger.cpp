// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTrigger.h"

#include "Components/StaticMeshComponent.h"
#include "Engine.h"

// Sets default values
ADoorTrigger::ADoorTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	Door->SetCollisionProfileName("BlockAll");
	DoorFrame->SetCollisionProfileName("OverlapAll");
	SetRootComponent(DoorFrame);
}

void ADoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = Door->GetComponentLocation();// GetActorLocation();
}

void ADoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentPos = Door->GetComponentLocation();// GetActorLocation();
	if (bOpen)
	{
		if (CurrentPos.Z < StartPosition.Z + MoveDistance)
		{
			CurrentPos.Z += MoveSpeed * DeltaTime;
			Door->SetWorldLocation(CurrentPos);// SetActorLocation(CurrentPos);
		}
		else
		{
			FVector NewPosition = StartPosition;
			NewPosition.Z += MoveDistance;
			Door->SetWorldLocation(NewPosition);  //SetActorLocation(NewPosition);
			bOpen = false;
		}
	}
	else if (bClose)
	{
		if (CurrentPos.Z > StartPosition.Z)
		{
			CurrentPos.Z -= MoveSpeed * DeltaTime;
			Door->SetWorldLocation(CurrentPos); //SetActorLocation(CurrentPos);
		}
		else
		{
			bClose = false;
			Door->SetWorldLocation(StartPosition);  //SetActorLocation(StartPosition);
		}
	}
}

void ADoorTrigger::Trigger()
{	
	/*FVector NewPosition = StartPosition;
	NewPosition.Z += MoveDistance;
	SetActorLocation(NewPosition);*/
	bOpen = true;
	bClose = false;
	if (NumOfTriggered == 0) UGameplayStatics::PlaySoundAtLocation(this, MoveSound, GetActorLocation());
	NumOfTriggered++;
	GEngine->AddOnScreenDebugMessage(-1, 5.000f, FColor::Orange, TEXT("[Enable] Current Door Number " + FString::SanitizeFloat(NumOfTriggered)));
}

void ADoorTrigger::DisableTrigger()
{
	if (NumOfTriggered > 0 ) NumOfTriggered--;
	GEngine->AddOnScreenDebugMessage(-1, 5.000f, FColor::Orange, TEXT("[Disable] Current Door Number " + FString::SanitizeFloat(NumOfTriggered)));
	if (NumOfTriggered == 0)
	{
		bOpen = false;
		bClose = true;
		UGameplayStatics::PlaySoundAtLocation(this, MoveSound, GetActorLocation());
		//SetActorLocation(StartPosition);
	}
}
