// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TossPotGameMode.generated.h"

UCLASS(minimalapi)
class ATossPotGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATossPotGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACameraMovement* CameraMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATossPotCharacter* Player1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATossPotCharacter* Player2;
	
	UPROPERTY(EditAnywhere)
		float SafeRange = 400.0f;

	UPROPERTY(EditAnywhere)
		float DeadZone = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CurrentDanger = 1.0f;

	void SwitchPlayers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};



