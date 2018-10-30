// Fill out your copyright notice in the Description page of Project Settings.

#include "SentryBot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Engine/World.h"
#include "MovementPoint.h"

#include "TossPotCharacter.h"

#include "Engine.h"


ASentryBot::ASentryBot()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Root"));

	m_TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Platform 1"));
	m_TBox->SetupAttachment(RootComponent);

	m_SearchBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SearchBox"));
	m_SearchBox->SetupAttachment(RootComponent);
}

void ASentryBot::BeginPlay()
{
	Super::BeginPlay();
	//SphereCollision->OnComponentBeginOverlap.Clear();
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AMovingCollectable::OnCompOverlap);


	m_TBox->OnComponentBeginOverlap.AddDynamic(this, &ASentryBot::OnOBoxOverlapBegin);

	m_SearchBox->OnComponentBeginOverlap.AddDynamic(this, &ASentryBot::OnOBoxOverlapBegin);

	m_SearchBox->OnComponentEndOverlap.AddDynamic(this, &ASentryBot::OnBoxOverlapEnd);

	if (fMovementSpeed == 0.0f)
	{
		fMovementSpeed = 100.0f;
	}
	OriginLocation = this->GetActorLocation();
	iCurrentPoint = 1;
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	bForward = true;
}
 
void ASentryBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("TICKING"));
	if (bRepeating && !bMoving)
	{
		//UE_LOG(LogTemp, Warning, TEXT("START MOVING"));
		bMoving = true;
	}
	if (bMoving && bForward && !IsColliding)
	{
		for (int i = 0; i < MovementPoints.Num(); i++)
		{
			if (MovementPoints[i]->iPointNum == iCurrentPoint)
			{
				//UE_LOG(LogTemp, Warning, TEXT("MOVING"));
				FVector destination;
				FRotator rotation;
				MovementPoints[i]->GetSocketWorldLocationAndRotation(FName(), destination, rotation);
				MoveTowards(destination, DeltaTime);
				if ((destination - GetActorLocation()).Size() < 10.0f)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Next Point: "));
					iCurrentPoint++;
					if (i + 1 < MovementPoints.Num())
					{
						FVector destination1;
						FRotator rotation1;
						FVector destination2;
						FRotator rotation2;
						MovementPoints[i]->GetSocketWorldLocationAndRotation(FName(), destination1, rotation1);
						MovementPoints[i + 1]->GetSocketWorldLocationAndRotation(FName(), destination2, rotation2);

						FVector FinalDir = destination2 - destination1;
						FVector axis = FVector(0, 0, 1);
						FinalDir = FinalDir.RotateAngleAxis(90, axis);
						FQuat FinalRotate = FinalDir.Rotation().Quaternion();
						SetActorRotation(FinalRotate);
					}
					else
					{
						FVector destination1;
						FRotator rotation1;
						FVector destination2;
						FRotator rotation2;
						MovementPoints[i]->GetSocketWorldLocationAndRotation(FName(), destination1, rotation1);
						MovementPoints[0]->GetSocketWorldLocationAndRotation(FName(), destination2, rotation2);

						FVector FinalDir = destination2 - destination1;
						FVector axis = FVector(0, 0, 1);
						FinalDir = FinalDir.RotateAngleAxis(90, axis);
						FQuat FinalRotate = FinalDir.Rotation().Quaternion();
						SetActorRotation(FinalRotate);
					}

				}
			}
		}
	}

	if (iCurrentPoint > MovementPoints.Num() && bRepeating)
	{
		iCurrentPoint = 1;
	}
	else if (iCurrentPoint > MovementPoints.Num())
	{
	}

	if (IsColliding && Toss)
	{
		WarningTime -= DeltaTime;
		AlertProtocol();
		UE_LOG(LogTemp, Warning, TEXT("Colliding"));
	}
	if (IsColliding == false)
	{
		WarningTime = 2;
	}

}

void ASentryBot::AlertProtocol()
{
	if (WarningTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning time over"));
		//Shoot that bitch
	}


}


void ASentryBot::OnOBoxOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	IsColliding = true;
}

void ASentryBot::OnBoxOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	IsColliding = false;
}


//void AMovingCollectable::OnCompOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	Super::OnCompOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
//	//UE_LOG(LogTemp, Warning, TEXT("SphereOver"));
//	ABirdPlayer* BirdRef = Cast<ABirdPlayer>(OtherActor);
//	if (BirdRef && !BirdRef->bRespawning)
//	{
//		bMoving = false;
//		//UE_LOG(LogTemp, Warning, TEXT("HIT"));
//	}
//
//}





void ASentryBot::MoveTowards(FVector _location, float DeltaTime)
{
	FVector PosNew;
	FVector Direction = _location - GetActorLocation();
	Direction.Normalize();
	Direction *= fMovementSpeed;
	PosNew = GetActorLocation() + (Direction * DeltaTime);
	SetActorLocation(PosNew);
	//UE_LOG(LogTemp, Warning, TEXT("Direction = %s"), *Direction.ToString());
}

