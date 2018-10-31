// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"

#include <vector>
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"



UCLASS()
class TOSSPOT_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ACheckpoint();

	UFUNCTION()
		void OnOBoxOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnBoxOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> ArrayOfActors;

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
	bool TossIsColliding = false;
	UPROPERTY(BlueprintReadOnly)
	bool PotIsColliding = false;
	class APotCharacter* Pot;
	class ATossCharacter* Toss;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* m_TBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_CurrentCheckPointPosition;

	UFUNCTION(BlueprintCallable)
		void Respawn(class ATossPotCharacter* Player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Restart();
	
	
};