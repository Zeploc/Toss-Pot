// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SentryBot.generated.h"


class UMovementPoint;
/**
 *
 */
UCLASS()
class TOSSPOT_API ASentryBot : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bRepeating;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fMovementSpeed;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//virtual void OnCompOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
		void OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TArray<class UMovementPoint*> MovementPoints;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* m_TBox;

	ASentryBot();
private:
	FVector OriginLocation;
	int iCurrentPoint;
	bool bMoving = false;


	void MoveTowards(FVector _location, float DeltaTime);
	bool bForward;
};

