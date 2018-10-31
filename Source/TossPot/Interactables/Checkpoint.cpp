// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


#include "TossPotCharacter.h"
#include "Player/TossCharacter.h"
#include "Player/PotCharacter.h"

#include "Engine.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Root"));

	m_TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Platform 1"));

	m_TBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	m_TBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOBoxOverlapBegin);
	m_TBox->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnBoxOverlapEnd);
	
}

void ACheckpoint::Respawn(ATossPotCharacter * Player)
{
	Player->SetActorLocation(m_CurrentCheckPointPosition);
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TossIsColliding && PotIsColliding)
	{
		m_CurrentCheckPointPosition = GetActorLocation();
	}
}

void ACheckpoint::OnOBoxOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APotCharacter* IsPot = Cast<APotCharacter>(OtherActor);
	ATossCharacter* IsToss = Cast<ATossCharacter>(OtherActor);
	if (IsToss)
	{
		TossIsColliding = true;
		Toss = IsToss;
	}
	if (IsPot)
	{
		PotIsColliding = true;
		Pot = IsPot;
	}
	
}

void ACheckpoint::OnBoxOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	APotCharacter* IsPot = Cast<APotCharacter>(OtherActor);
	ATossCharacter* IsToss = Cast<ATossCharacter>(OtherActor);

	if (IsToss)
	{
		TossIsColliding = false;
		Toss = IsToss;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Toss On Converor Belt!");

	}

	if (IsPot)
	{
		PotIsColliding = false;
		Pot = IsPot;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Toss On Converor Belt!");

	}

}

