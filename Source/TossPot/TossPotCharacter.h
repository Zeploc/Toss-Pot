// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TossPotCharacter.generated.h"

UCLASS(config=Game)
class ATossPotCharacter : public ACharacter
{
	GENERATED_BODY()


protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Called for side to side input */
	void MoveUp(float Val);

	///** Handle touch inputs. */
	//void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	///** Handle touch stop event. */
	//void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	ATossPotCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact();

	void Death(FVector SpawnPos);
	void RespawnPlayer();

	UPROPERTY(EditAnywhere)
		float InteractRange = 100.0f;

	FVector SpawningPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnDelay = 1.0f;
	
	FTimerHandle RespawnDelay;
};
