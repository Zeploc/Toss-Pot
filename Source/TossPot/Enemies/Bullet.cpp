// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/TossCharacter.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

#include "Engine.h"

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	//SetVelocity

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Root"));

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Static Mesh"));
	BoxMesh->SetupAttachment(RootComponent);

	ProjectileMotion = CreateDefaultSubobject <UProjectileMovementComponent>(TEXT("Projectile"));


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));
	CollisionBox->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);


}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATossCharacter* IsToss = Cast<ATossCharacter>(OtherActor);
	if (IsToss)
	{
		IsColliding = true;
		Toss = IsToss;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Toss On big Converor Belt!");

	}
}

void ABullet::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ATossCharacter* IsToss = Cast<ATossCharacter>(OtherActor);

	if (IsToss)
	{
		IsColliding = false;
		Toss = IsToss;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Toss On Converor Belt!");

	}
}
