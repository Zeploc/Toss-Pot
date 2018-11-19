// Fill out your copyright notice in the Description page of Project Settings.

#include "MagneticWall.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Player/PotCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AMagneticWall::AMagneticWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	BoxCollision->SetupAttachment(RootComponent);
	ArrowComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMagneticWall::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMagneticWall::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMagneticWall::OnOverlapEnd);
}

void AMagneticWall::Trigger()
{
	ATriggerActor::Trigger();
	//Animation for when the magnet wall is disabled here
}

void AMagneticWall::DisableTrigger()
{
	ATriggerActor::DisableTrigger();
	//Animation for when the magnet wall is enable go here
}

// Called every frame
void AMagneticWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Triggered)
	{
		//DisableTrigger();
		if (isOverlaping && isPot)
		{
			if (isPot->GetVelocity().Size() < MaxMoveSpeed)
				isPot->LaunchCharacter((ArrowComponent->GetForwardVector() * fPushBackForce), false, false);
		}
	}
	/*else if (ATriggerActor::Triggered)
	{
		Trigger();
	}*/
	
}

void AMagneticWall::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	isPot = Cast<APotCharacter>(OtherActor);
	if (isPot)
	{
		isOverlaping = true;
	}

}

void AMagneticWall::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	isPot = Cast<APotCharacter>(OtherActor);
	if (isPot)
	{
		isOverlaping = false;
	}
}



