// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractActor.h"
#include "TimedInteractLever.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API ATimedInteractLever : public AInteractActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class USkeletalMeshComponent* LeverMesh;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UBoxComponent* Collision;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATriggerActor* TriggerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DelayTime = 1.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool TickingDown = false;

private:
	bool bOverlapping = false;


	UFUNCTION()
		void OnLeverOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnLeverEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Sets default values for this actor's properties
	ATimedInteractLever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TickingTimeHandle;
	void DisableTrigger();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	UFUNCTION(BlueprintCallable)
		virtual void Reset() override;
	
};
