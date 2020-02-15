// Fill out your copyright notice in the Description page of Project Settings.

#include "SwitchPlayersPad.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "TossPotGameMode.h"

#include "Player/TossPotCharacter.h"

#include "Engine.h"

// Sets default values
ASwitchPlayersPad::ASwitchPlayersPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pad Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	SetRootComponent(PadMesh);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitchPlayersPad::OnTriggerOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASwitchPlayersPad::OnTriggerEndOverlap);
	TriggerBox->SetupAttachment(PadMesh);
	TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

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
		bEnabled = false;
		ButtonMID->SetScalarParameterValue("Lit", 0.0f);
	}
}

void ASwitchPlayersPad::OnInteract()
{
	if (Overlapped && !Switching && OtherSwitch)
	{
		ButtonMID->SetScalarParameterValue("Lit", 1.0f);
		bEnabled = true;
		if (OtherSwitch->bEnabled)
		{
			Switching = true;
			OtherSwitch->Switching = true;
			GetWorldTimerManager().SetTimer(SwitchingDelay, this, &ASwitchPlayersPad::SwitchPlayers, SwitchDelayTime, false);
			APlayerController* Player1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			APlayerController* Player2 = UGameplayStatics::GetPlayerController(GetWorld(), 1);
			if (Player1) Player1->GetCharacter()->DisableInput(Player1);
			if (Player2) Player2->GetCharacter()->DisableInput(Player2);
		}
	}
}

void ASwitchPlayersPad::SwitchPlayers()
{
	GetWorldTimerManager().ClearTimer(SwitchingDelay);
	Switching = false;
	OtherSwitch->Switching = false;

	APlayerController* Player1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* Player2 = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	if (Player1) Player1->GetCharacter()->EnableInput(Player1);
	if (Player2) Player2->GetCharacter()->EnableInput(Player2);

	if (HasAuthority())
	{
		if (ATossPotGameMode* TossPotGameMode = Cast<ATossPotGameMode>(GetWorld()->GetAuthGameMode()))
		{
			TossPotGameMode->SwitchPlayers();
		}
	}

	ACharacter* Player1Character;
	if (Player1)
		Player1Character = Player1->GetCharacter();
	else
		Player1Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	ACharacter* Player2Character;
	if (Player2)
		Player2Character = Player2->GetCharacter();
	else
		Player2Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);

	if (!Player1Character || !Player2Character)
		return;

	FVector P1Loc = Player1Character->GetActorLocation();
	FVector P2Loc = Player2Character->GetActorLocation();
	P1Loc.Z += 50.0f;
	P2Loc.Z += 50.0f;
	Player1->GetCharacter()->SetActorLocation(P1Loc);
	Player2->GetCharacter()->SetActorLocation(P2Loc);

}