// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractActor.h"
#include "Components/BoxComponent.h"
#include "Triggers/TriggerActor.h"
#include "InteractOverlap.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API AInteractOverlap : public AInteractActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UBoxComponent* OverlapColliderBox;

	UPROPERTY(EditAnywhere)
		ATriggerActor* TriggerActor;


public:
	// Sets default values for this actor's properties
	AInteractOverlap();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
