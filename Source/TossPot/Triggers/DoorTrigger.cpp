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
	Door->SetCollisionProfileName("BlockAll");
}

void ADoorTrigger::BeginPlay()
{
	StartPosition = GetActorLocation();
}

void ADoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorTrigger::Trigger()
{	
	FVector NewPosition = StartPosition;
	NewPosition.Z += MoveDistance;
	SetActorLocation(NewPosition);
	NumOfTriggered++;
	GEngine->AddOnScreenDebugMessage(-1, 5.000f, FColor::Orange, TEXT("Current Door Number " + FString::SanitizeFloat(NumOfTriggered)));
}

void ADoorTrigger::DisableTrigger()
{
	if (NumOfTriggered > 0 ) NumOfTriggered--;
	GEngine->AddOnScreenDebugMessage(-1, 5.000f, FColor::Orange, TEXT("Current Door Number " + FString::SanitizeFloat(NumOfTriggered)));
	if (NumOfTriggered == 0)
		SetActorLocation(StartPosition);
}
