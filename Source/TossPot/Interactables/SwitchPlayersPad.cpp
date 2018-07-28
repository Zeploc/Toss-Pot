// Fill out your copyright notice in the Description page of Project Settings.

#include "SwitchPlayersPad.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "TossPotGameMode.h"

#include "TossPotCharacter.h"

#include "Engine.h"

// Sets default values
ASwitchPlayersPad::ASwitchPlayersPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	SetRootComponent(PadMesh);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitchPlayersPad::OnTriggerOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASwitchPlayersPad::OnTriggerEndOverlap);

}
// Called when the game starts or when spawned
void ASwitchPlayersPad::BeginPlay()
{
	Super::BeginPlay();

	ButtonMID = UMaterialInstanceDynamic::Create(PadMesh->GetMaterial(0), this);
	PadMesh->SetMaterial(0, ButtonMID);
}

void ASwitchPlayersPad::OnTriggerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ATossPotCharacter>(OtherActor))
	{
		Overlapped = true;
	}
}

void ASwitchPlayersPad::OnTriggerEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ATossPotCharacter>(OtherActor))
	{
		Overlapped = false;
		Enabled = false;
		ButtonMID->SetScalarParameterValue("Lit", 0.0f);
	}
}

void ASwitchPlayersPad::Interact()
{
	if (Overlapped)
	{
		ButtonMID->SetScalarParameterValue("Lit", 1.0f);
		Enabled = true;
		if (OtherSwitch->Enabled)
		{
			Cast<ATossPotGameMode>(GetWorld()->GetAuthGameMode())->SwitchPlayers();
		}
	}
}