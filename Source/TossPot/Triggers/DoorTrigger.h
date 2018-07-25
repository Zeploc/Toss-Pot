// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggers/TriggerActor.h"
#include "DoorTrigger.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API ADoorTrigger : public ATriggerActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int NumOfTriggered = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Trigger();
	virtual void DisableTrigger();
	
	UPROPERTY(EditAnywhere)
		float MoveDistance = 200.0f;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 400.0f;

	FVector StartPosition;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorFrame;

	bool bOpen = false;
	bool bClose = false;
	
};
