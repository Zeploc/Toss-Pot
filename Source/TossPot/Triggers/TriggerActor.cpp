// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerActor.h"
#include "Engine.h"

#include "UnrealNetwork.h"


// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called every frame
void ATriggerActor::Trigger()
{
	Triggered = true;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using base trigger (Trigger not set)"));

}

// Called every frame
void ATriggerActor::DisableTrigger()
{
	Triggered = false;

}

void ATriggerActor::Toggle()
{
	if (Triggered)
		DisableTrigger();
	else
		Trigger();
}

void ATriggerActor::Reset()
{
	Triggered = false;
}

void ATriggerActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATriggerActor, Triggered);
}