// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractActor.h"
#include "InteractLever.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API AInteractLever : public AInteractActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* LeverMesh;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Collision;


	UPROPERTY(EditAnywhere)
		class ATriggerActor* TriggerActor;

	UPROPERTY(EditAnywhere)
		float DelayTime = 0;

	bool bOverlapping = false;
	
	FRotator LeverOffRotation;
	
	UFUNCTION()
		void OnLeverOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnLeverEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Sets default values for this actor's properties
	AInteractLever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTimerHandle DisableTriggerDelay;
	void DisableTrigger();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact();
};
