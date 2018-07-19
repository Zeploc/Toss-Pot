// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTrigger.h"

// Sets default values
ADoorTrigger::ADoorTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADoorTrigger::BeginPlay()
{
	StartPosition = DoorActor->GetActorLocation();
}

void ADoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorTrigger::Trigger()
{	
	FVector NewPosition = StartPosition;
	NewPosition.Z += MoveDistance;
	DoorActor->SetActorLocation(NewPosition);
}

void ADoorTrigger::DisableTrigger()
{
	DoorActor->SetActorLocation(StartPosition);
}
