// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractLever.h"

#include "Components/StaticMeshComponent.h"
#include "Triggers/TriggerActor.h"
#include "Engine.h"


// Sets default values
AInteractLever::AInteractLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Mesh"));
	LeverMesh->SetCollisionProfileName("OverlapAll");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetCollisionProfileName("BlockAll");
	Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	SetRootComponent(BaseMesh);

	Collision->SetVisibility(false);
	Collision->SetCollisionObjectType(ECC_GameTraceChannel1);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AInteractLever::OnLeverOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AInteractLever::OnLeverEndOverlap);

	LeverOffRotation = LeverMesh->GetComponentRotation();
}

// Called when the game starts or when spawned
void AInteractLever::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractLever::Interact()
{
	if (!bOverlapping) return;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using Interact Lever Interact Function"));
	if (LeverMesh->GetComponentRotation().Pitch <= LeverOffRotation.Pitch)
	{
		FRotator OnRotation = LeverOffRotation;
		OnRotation.Pitch += 100.0f;
		LeverMesh->SetRelativeRotation(OnRotation);			
	}
	else
	{
		LeverMesh->SetRelativeRotation(LeverOffRotation);
	}
	
	if (TriggerActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Trigger Actor Not set!"));
		return;
	}
	TriggerActor->Trigger();
}

void AInteractLever::DisableTrigger()
{
	TriggerActor->DisableTrigger();
	GetWorldTimerManager().ClearTimer(DisableTriggerDelay);
}


void AInteractLever::OnLeverOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bOverlapping = true;
}

void AInteractLever::OnLeverEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bOverlapping = false;
}
