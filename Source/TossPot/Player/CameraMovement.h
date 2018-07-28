// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraMovement.generated.h"

UCLASS()
class TOSSPOT_API ACameraMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATossPotCharacter* Player1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATossPotCharacter* Player2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CloseBoomArmLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CloseBoomArmZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float MinPosY = -350;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float MaxPosY = 150;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DistanceMaxY = 400;


	UFUNCTION(BlueprintCallable)
		void SetControllersView();
};
