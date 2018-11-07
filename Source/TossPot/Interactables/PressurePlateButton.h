// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactables/InteractActor.h"
#include "PressurePlateButton.generated.h"

UCLASS()
class TOSSPOT_API APressurePlateButton : public AActor
{
	GENERATED_BODY()


	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere)
		class ATriggerActor* TriggerActor;
		

	UFUNCTION()
		void OnButtonOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

public:	
	// Sets default values for this actor's properties
	APressurePlateButton();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* Plate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* Button;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* PressSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ReleaseSound;

	void Reset();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsOverlapping = false;
	bool MoveUp = false;

	void ChangeLight(bool _bLit);

	FTimerHandle OverlapDelayHandler;
	void OverlapDelay();
	FTimerHandle TriggerDelayHandler;
	void Trigger();
	void ReleaseTrigger();

	FVector OriginalButtonPosition;
	
	int NumOnButton = 0;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReturnTime = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EInteractMode InteractMode = EInteractMode::EI_HOLD;

	bool Activated = false;
	
	UMaterialInstanceDynamic* ButtonMID;

};
