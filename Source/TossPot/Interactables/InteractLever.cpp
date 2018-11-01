// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractLever.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Triggers/TriggerActor.h"
#include "Triggers/DoorTrigger.h"
#include "TossPotCharacter.h"
#include "Engine.h"


// Sets default values
AInteractLever::AInteractLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lever Mesh"));
	LeverMesh->SetCollisionProfileName("BlockAll");
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Interact Trigger"));
	SetRootComponent(LeverMesh);

	//Collision->SetVisibility(false);
	Collision->SetCollisionObjectType(ECC_GameTraceChannel1);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AInteractLever::OnLeverOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AInteractLever::OnLeverEndOverlap);

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
	//if (!bOverlapping) return;
	if (TriggerActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Trigger Actor Not set!"));
		return;
	}
	bool bIsDoor = Cast<ADoorTrigger>(TriggerActor) != nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using Interact Lever Interact Function"));
	if (!bEnabled)
	{
		bEnabled = true;
		/*FRotator OnRotation = LeverOffRotation;
		OnRotation.Pitch += 100.0f;
		LeverMesh->SetRelativeRotation(OnRotation);		*/	
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
		TriggerActor->Trigger();
	}
	else
	{
		bEnabled = false;
		/*LeverMesh->SetRelativeRotation(LeverOffRotation);*/
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
		if (bIsDoor) TriggerActor->DisableTrigger();
		else TriggerActor->Trigger();
	}
	
}

void AInteractLever::DisableTrigger()
{
	TriggerActor->DisableTrigger();
	GetWorldTimerManager().ClearTimer(DisableTriggerDelay);
}


void AInteractLever::OnLeverOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ATossPotCharacter>(OtherActor))
		bOverlapping = true;
}

void AInteractLever::OnLeverEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ATossPotCharacter>(OtherActor))
		bOverlapping = false;
}
