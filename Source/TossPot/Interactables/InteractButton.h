// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactables/InteractActor.h"
#include "Triggers/TriggerActor.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "InteractButton.generated.h"

UCLASS()
class TOSSPOT_API AInteractButton : public AInteractActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
		ATriggerActor* TriggerActor;

	UPROPERTY(EditAnywhere)
		float DelayTime = 0;

public:	
	// Sets default values for this actor's properties
	AInteractButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAnimSequence* PushAnimation;

	FTimerHandle DisableTriggerDelay;
	void DisableTrigger();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnInteract();
	
};
