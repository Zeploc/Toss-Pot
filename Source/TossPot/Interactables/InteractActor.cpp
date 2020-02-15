// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractActor.h"
#include "Engine.h"

#include "Kismet/GameplayStatics.h"

#include "NetworkSession/NetworkInitialiseComponent.h"

#include "TossPotGameMode.h"
#include "Player/TossPotCharacter.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	NetworkInitialiseComponent = CreateDefaultSubobject<UNetworkInitialiseComponent>(TEXT("Network Initialise Component"));
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractActor::Interact()
{
	if (HasAuthority())
	{
		MULTI_Interact();
	}
	else
	{
		SERVER_Interact();
		OnInteract();
	}
}
void AInteractActor::SERVER_Interact_Implementation()
{
	OnInteract();
}
bool AInteractActor::SERVER_Interact_Validate()
{
	return true;
}
void AInteractActor::MULTI_Interact_Implementation()
{
	OnInteract();
}

void AInteractActor::OnInteract()
{
	bEnabled = !bEnabled;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using Base Interact (Interact Actor as no interact override)"));
}


void AInteractActor::Initialise_Implementation()
{
	if (!HasAuthority())
	{
		return;
	}

	if (GetWorld())
	{
		if (GetWorld()->GetAuthGameMode())
		{
			if (ATossPotGameMode* TossPotGameMode = Cast<ATossPotGameMode>(GetWorld()->GetAuthGameMode()))
			{
				if (TossPotGameMode->Player2)
				{
					SetOwner(TossPotGameMode->Player2);

				}
			}
		}
	}
	
}

void AInteractActor::Reset()
{
	bEnabled = false;
}

