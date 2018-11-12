// Fill out your copyright notice in the Description page of Project Settings.

#include "ConveyorBelt.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Player/TossCharacter.h"

#include "Engine.h"

// Sets default values
AConveyorBelt::AConveyorBelt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Root"));

	ConveyorBeltMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Conveyor Belt Static Mesh"));
	ConveyorBeltMesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));
	CollisionBox->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	
}


// Called when the game starts or when spawned
void AConveyorBelt::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AConveyorBelt::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AConveyorBelt::OnOverlapEnd);
}

// Called every frame
void AConveyorBelt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsColliding && Toss && Triggered)
	{
		FVector ForwardVector = GetActorForwardVector();
		ForwardVector *= PushSpeed;
		Toss->LaunchCharacter((ArrowComponent->GetForwardVector() * PushSpeed), false, false);
	}
}

void AConveyorBelt::Trigger()
{
	Triggered = true;
}

void AConveyorBelt::DisableTrigger()
{
	Triggered = false;
}


void AConveyorBelt::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATossCharacter* IsToss = Cast<ATossCharacter>(OtherActor);
	if (IsToss)
	{
		IsColliding = true;
		Toss = IsToss;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Toss On big Converor Belt!");
		
	}
}

void AConveyorBelt::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ATossCharacter* IsToss = Cast<ATossCharacter>(OtherActor);

	if (IsToss)
	{
		IsColliding = false;
		Toss = IsToss;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Toss On Converor Belt!");

	}
}

