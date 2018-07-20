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

	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATossPotCharacter* Player1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATossPotCharacter* Player2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};



