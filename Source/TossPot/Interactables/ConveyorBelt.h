// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Triggers/TriggerActor.h"
#include "ConveyorBelt.generated.h"

UCLASS()
class TOSSPOT_API AConveyorBelt : public ATriggerActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConveyorBelt();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* ConveyorBeltMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UArrowComponent* ArrowComponent;
	
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Trigger() override;
	virtual void DisableTrigger()override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "fug")
		float PushSpeed = 100.0f;


private:
	bool IsColliding = false;
	class ATossCharacter* Toss;
	
	
};
