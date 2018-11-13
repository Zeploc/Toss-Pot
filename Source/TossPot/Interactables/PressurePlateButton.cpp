// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlateButton.h"
#include "ConstructorHelpers.h"
#include "Engine.h"

#include "Engine/StaticMesh.h"
#include "Triggers/TriggerActor.h"
#include "TossPotCharacter.h"

// Sets default values
APressurePlateButton::APressurePlateButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Boy"));
	Plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate Contianer Mesh"));
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Cylinder Collider Mesh"));
	SetRootComponent(Plate);// RootComponent);
	//Plate->SetupAttachment(RootComponent);
	Button->SetupAttachment(Plate);
	Button->RelativeLocation = FVector(0.0f, 0.0f, 30.0f);
	Button->SetConstraintMode(EDOFMode::SixDOF);
	

	BoxTrigger->SetWorldScale3D(FVector(1.7f, 1.7f, 0.45f));
	BoxTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 23.0f));
	BoxTrigger->SetVisibility(false);
	BoxTrigger->SetCollisionProfileName("OverlapAll");
	BoxTrigger->SetupAttachment(Button);
	
	Plate->SetMobility(EComponentMobility::Static);
	Button->SetMobility(EComponentMobility::Movable);

	Button->SetSimulatePhysics(false);

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &APressurePlateButton::OnButtonOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &APressurePlateButton::OnButtonEndOverlap);

	//Button->SetAbsolute(false, true, true);
}

void APressurePlateButton::Reset()
{
	//IsOverlapping = false;
	//MoveUp = false;
	//Button->SetSimulatePhysics(false);
	Activated = false;
	Button->SetSimulatePhysics(false);
	MoveUp = true;
	IsOverlapping = false;
}

// Called when the game starts or when spawned
void APressurePlateButton::BeginPlay()
{
	Super::BeginPlay();
	OriginalButtonPosition = Button->GetComponentLocation();

	ButtonMID = UMaterialInstanceDynamic::Create(Button->GetMaterial(0), this);
	Button->SetMaterial(0, ButtonMID);
}

void APressurePlateButton::ChangeLight(bool _bLit)
{
	if (_bLit)
	{
		ButtonMID->SetScalarParameterValue("Lit", 1.0f);
	}
	else
	{
		ButtonMID->SetScalarParameterValue("Lit", 0.0f);
	}
}

void APressurePlateButton::OverlapDelay()
{
	if (IsOverlapping == false)
	{
		GetWorldTimerManager().ClearTimer(OverlapDelayHandler);
		ReleaseTrigger();
	}
}

void APressurePlateButton::Trigger()
{
	if (InteractMode == EInteractMode::EI_ONEOFF && Activated) // One off and already triggered
		return;

	Button->SetSimulatePhysics(true);
	MoveUp = false;
	Activated = true;
	if (TriggerActor != nullptr)
	{
		if (InteractMode == EInteractMode::EI_TOGGLE && Activated) // Toggle and already activated
		{
			Activated = false;
			TriggerActor->Toggle(); // Toggle
			//TriggerActor->DisableTrigger(); // Disable
		}
		else if (InteractMode == EInteractMode::EI_ONEOFF)
		{
			if (TriggerActor->Triggered) // If is one off and is already triggered (from another interact actor)
				TriggerActor->DisableTrigger();
			else // One off trigger
				TriggerActor->Trigger();
		}
		else if (!TriggerActor->Triggered)
			TriggerActor->Trigger(); // normal enable
	}
	// Light Up
	ChangeLight(true);
	// Enable sound
	UGameplayStatics::PlaySoundAtLocation(this, PressSound, GetActorLocation());

}

void APressurePlateButton::ReleaseTrigger()
{
	if (InteractMode == EInteractMode::EI_ONEOFF && Activated) // One off don't release
		return;

	Button->SetSimulatePhysics(false);
	MoveUp = true;
	// Disable Sound
	UGameplayStatics::PlaySoundAtLocation(this, ReleaseSound, GetActorLocation());
	// Turn off light
	ChangeLight(false);

	if (TriggerActor != nullptr && InteractMode != EInteractMode::EI_TOGGLE) // If not toggle, can disable trigger
	{
		TriggerActor->DisableTrigger();
	}
	Activated = false;
}

void APressurePlateButton::OnButtonOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OverlappedComp != Plate && OverlappedComp != Button && OtherActor != this && Cast <ATossPotCharacter>(OtherActor))
	{
		NumOnButton++;
		if (GetWorldTimerManager().TimerExists(OverlapDelayHandler))
		{
			GetWorldTimerManager().ClearTimer(OverlapDelayHandler);
			return;
		}
		if (NumOnButton > 1)
			return;

		IsOverlapping = true;
		Trigger();
	}
}

void APressurePlateButton::OnButtonEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComp != Plate && OverlappedComp != Button && OtherActor != this && Cast <ATossPotCharacter>(OtherActor))
	{
		if (NumOnButton > 0) NumOnButton--;
		if (NumOnButton > 0)
		{
			return;
		}
		IsOverlapping = false;
		if (ReturnTime != 0.0f) GetWorldTimerManager().SetTimer(OverlapDelayHandler, this, &APressurePlateButton::OverlapDelay, ReturnTime, false);
		else OverlapDelay();
	}
}

// Called every frame
void APressurePlateButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MoveUp == true && IsOverlapping == false)
	{
		
		if (Button->GetComponentLocation().Z < OriginalButtonPosition.Z)
		{
			Button->MoveComponent(Button->GetUpVector(), Button->GetComponentRotation(), true);
		}
		else
		{
			MoveUp = false;
			Button->SetRelativeLocation(OriginalButtonPosition);
		}
	}
	if (Button->GetComponentLocation().X != Plate->GetComponentLocation().X)
	{
		FVector Newlocation = Button->GetComponentLocation();
		Newlocation.X = Plate->GetComponentLocation().X;
		Button->SetWorldLocation(Newlocation);
	}
	if (Button->GetComponentLocation().Y != Plate->GetComponentLocation().Y)
	{
		FVector Newlocation = Button->GetComponentLocation();
		Newlocation.Y = Plate->GetComponentLocation().Y;
		Button->SetWorldLocation(Newlocation);
	}	
}

