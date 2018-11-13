// Fill out your copyright notice in the Description page of Project Settings.

#include "TimedInteractLever.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TossPotCharacter.h"
#include "Triggers/TriggerActor.h"
#include "Engine.h"

ATimedInteractLever::ATimedInteractLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lever Mesh"));
	LeverMesh->SetCollisionProfileName("BlockAll");
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Interact Trigger"));
	SetRootComponent(LeverMesh);

	//Collision->SetVisibility(false);
	Collision->SetCollisionObjectType(ECC_GameTraceChannel1);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ATimedInteractLever::OnLeverOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ATimedInteractLever::OnLeverEndOverlap);
}


void ATimedInteractLever::BeginPlay()
{
	Super::BeginPlay();
}

void ATimedInteractLever::DisableTrigger()
{
	TriggerActor->DisableTrigger();
	GetWorldTimerManager().ClearTimer(TickingTimeHandle);
	TickingDown = false;
	bEnabled = false;
}

void ATimedInteractLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimedInteractLever::Interact()
{
	//if (!bOverlapping) return;
	if (TriggerActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Trigger Actor Not set!"));
		return;
	}
	bEnabled = true;
	if (TickingDown)
	{
		//GetWorldTimerManager().ClearTimer(TickingTimeHandle);
		//GetWorldTimerManager().SetTimer(TickingTimeHandle, this, &ATimedInteractLever::DisableTrigger, DelayTime, false);
		return;
	}

	TickingDown = true;
	GetWorldTimerManager().SetTimer(TickingTimeHandle, this, &ATimedInteractLever::DisableTrigger, DelayTime, false);
	TriggerActor->Trigger();


	/*bool bIsDoor = Cast<ADoorTrigger>(TriggerActor) != nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using Interact Lever Interact Function"));
	if (!bEnabled)
	{
		bEnabled = true;
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
		TriggerActor->Trigger();
	}
	else
	{
		bEnabled = false;
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
		if (bIsDoor) TriggerActor->DisableTrigger();
		else TriggerActor->Trigger();
	}*/
}

void ATimedInteractLever::Reset()
{

}


void ATimedInteractLever::OnLeverOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ATossPotCharacter>(OtherActor))
		bOverlapping = true;
}

void ATimedInteractLever::OnLeverEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ATossPotCharacter>(OtherActor))
		bOverlapping = false;
}