// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerActor.h"
#include "Engine.h"


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

	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::Green, TEXT("BASE TICK RUNNING"));
}

// Called every frame
void ATriggerActor::Trigger()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using base trigger (Trigger not set)"));

}
// Called every frame
void ATriggerActor::DisableTrigger()
{


}
