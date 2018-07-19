// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTrigger.h"

#include "Components/StaticMeshComponent.h"

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
}

void ADoorTrigger::DisableTrigger()
{
	NumOfTriggered--;
	if (NumOfTriggered == 0)
		SetActorLocation(StartPosition);
}
