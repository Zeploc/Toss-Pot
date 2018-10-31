// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Triggers/TriggerActor.h"
#include "Interactables/InteractActor.h"
#include "MagneticWall.generated.h"



UCLASS()
class TOSSPOT_API AMagneticWall : public ATriggerActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMagneticWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Trigger();
	virtual void DisableTrigger();




public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fPushBackForce = 500.0f;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* MagneticActivate;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* MagneticDeActivate;
	
private:

	class ACharacter* isPot = nullptr;
	bool isOverlaping = false;
};
