// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TossPotCharacter.h"
#include "PotCharacter.generated.h"


/**
 * 
 */
UCLASS()
class TOSSPOT_API APotCharacter : public ATossPotCharacter
{
	GENERATED_BODY()
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	void PotJump();
	void PotStopJump();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UParticleSystemComponent* ParticleSystem;
public:

	APotCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* JumpSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CurrentlyJumping = false;
};
