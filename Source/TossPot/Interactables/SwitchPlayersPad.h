// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractActor.h"
#include "SwitchPlayersPad.generated.h"

/**
 * 
 */
UCLASS()
class TOSSPOT_API ASwitchPlayersPad : public AInteractActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwitchPlayersPad();

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* PadMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* TriggerBox;


	UFUNCTION()
		void OnTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool Overlapped = false;
	bool Enabled = false;

	UMaterialInstanceDynamic* ButtonMID;
	
	UPROPERTY(EditAnywhere)
		ASwitchPlayersPad* OtherSwitch;

	virtual void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};