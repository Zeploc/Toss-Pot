// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementPoint.h"
#include "SentryBot.h"

// Sets default values for this component's properties
UMovementPoint::UMovementPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	iPointNum = 0;

	// ...
}


// Called when the game starts
void UMovementPoint::BeginPlay()
{
	Super::BeginPlay();
	if (ASentryBot* owner = Cast<ASentryBot>(GetOwner()))
	{
		owner->MovementPoints.Add(this);
		this->bAbsoluteLocation = true;
		this->bAbsoluteRotation = true;
		this->bAbsoluteScale = true;
	}
	// ...

}


// Called every frame
void UMovementPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}