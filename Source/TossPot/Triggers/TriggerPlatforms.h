// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggers/TriggerActor.h"
#include "TriggerPlatforms.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API ATriggerPlatforms : public ATriggerActor
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	ATriggerPlatforms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Trigger();
	virtual void DisableTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Platform1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Platform2;

	FVector StartPostion1;
	FVector StartPostion2;

	UPROPERTY(EditDefaultsOnly)
		FVector EndPostion1;

	UPROPERTY(EditDefaultsOnly)
		FVector EndPostion2;

	bool bPlatform1DirectionForward = true;
	bool bPlatform2DirectionForward = true;

	UPROPERTY(EditDefaultsOnly)
		float Platform1Speed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
		float Platform2Speed = 1.0f;
};
