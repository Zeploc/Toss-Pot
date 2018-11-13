// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTrigger.h"

#include "Components/StaticMeshComponent.h"
#include "Engine.h"

// Sets default values
ADoorTrigger::ADoorTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Door"));
	//Door->SetCollisionProfileName("BlockAll");
	SetRootComponent(Door);
}

void ADoorTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ADoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorTrigger::Trigger()
{	
	ATriggerActor::Trigger();
	/*FVector NewPosition = StartPosition;
	NewPosition.Z += MoveDistance;
	SetActorLocation(NewPosition);*/
	//bOpen = true;
	//bClose = false;
	if (NumOfTriggered == 0) UGameplayStatics::PlaySoundAtLocation(this, MoveSound, GetActorLocation());
	NumOfTriggered++;
	GEngine->AddOnScreenDebugMessage(-1, 5.000f, FColor::Orange, TEXT("[Enable] Current Door Number " + FString::SanitizeFloat(NumOfTriggered)));
}

void ADoorTrigger::DisableTrigger()
{
	ATriggerActor::DisableTrigger();
	if (NumOfTriggered > 0 ) NumOfTriggered--;
	GEngine->AddOnScreenDebugMessage(-1, 5.000f, FColor::Orange, TEXT("[Disable] Current Door Number " + FString::SanitizeFloat(NumOfTriggered)));
	if (NumOfTriggered == 0)
	{
		//bOpen = false;
		//bClose = true;
		UGameplayStatics::PlaySoundAtLocation(this, MoveSound, GetActorLocation());
		//SetActorLocation(StartPosition);
	}
}

void ADoorTrigger::Reset()
{
	ATriggerActor::Reset();
	NumOfTriggered = 0;
	Open = true;
}
