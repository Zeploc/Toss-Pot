// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetworkSession/NetworkInitialiseInterface.h"
#include "InteractActor.generated.h"

UENUM(BlueprintType)
enum class EInteractMode : uint8
{
	EI_HOLD UMETA(DisplayName = "Hold"),
	EI_ONEOFF UMETA(DisplayName = "One Off"),
	EI_TOGGLE UMETA(DisplayName = "Toggle"),
};

UCLASS()
class TOSSPOT_API AInteractActor : public AActor, public INetworkInitialiseInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActor();

	class UNetworkInitialiseComponent* NetworkInitialiseComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact();
	UFUNCTION(Server, WithValidation, Reliable)
		void SERVER_Interact();
	UFUNCTION(NetMulticast, Reliable)
		void MULTI_Interact();


	virtual void OnInteract();
	

	virtual void Initialise_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = false;

	UFUNCTION(BlueprintCallable)
		virtual void Reset();

};
