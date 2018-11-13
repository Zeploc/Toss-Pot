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

	UFUNCTION(BlueprintCallable)
		virtual void Reset() override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Rail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Platform2;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* MovingSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		UAudioComponent* MovementAudioComponent;

	FVector RailPosition;
	FVector StartPostion1;
	FVector StartPostion2;

	UPROPERTY(BlueprintReadWrite)
		FVector EndPostion1;

	UPROPERTY(EditAnywhere)
		FVector EndPostion2;

	bool bPlatform1DirectionForward = false;
	bool bPlatform2DirectionForward = false;

	bool bPlatform1Move = false;
	bool bPlatform2Move = false;

	UPROPERTY(EditAnywhere)
		float Platform1Speed = 500.0f;

	UPROPERTY(EditAnywhere)
		float Platform2Speed = 500.0f;
};
