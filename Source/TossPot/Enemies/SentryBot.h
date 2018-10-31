// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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

	void AlertProtocol();

	//virtual void OnCompOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
		void OnOBoxOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnBoxOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<class UMovementPoint*> MovementPoints;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* m_TBox;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* m_SearchBox;

	ASentryBot();
private:
	bool IsColliding = false;
	FVector OriginLocation;
	int iCurrentPoint;
	bool bMoving = false;
	class ATossPotCharacter* Toss; // Could be wrong class
	int WarningTime = 2;

	void MoveTowards(FVector _location, float DeltaTime);
	bool bForward;
};

