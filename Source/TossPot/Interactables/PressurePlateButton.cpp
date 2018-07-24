// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlateButton.h"
#include "ConstructorHelpers.h"
#include "Engine.h"

#include "Engine/StaticMesh.h"
#include "Triggers/TriggerActor.h"

// Sets default values
APressurePlateButton::APressurePlateButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate Contianer Mesh"));
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	CylinderCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder Collider Mesh"));
	Button->SetupAttachment(Plate);
	Button->RelativeLocation = FVector(0.0f, 0.0f, 30.0f);
	Button->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));

	CylinderCollider->SetWorldScale3D(FVector(1.7f, 1.7f, 0.45f));
	CylinderCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 23.0f));
	CylinderCollider->SetVisibility(false);
	CylinderCollider->SetCollisionProfileName("OverlapAll");
	CylinderCollider->SetupAttachment(Button);
	
	Plate->SetMobility(EComponentMobility::Static);
	Button->SetMobility(EComponentMobility::Movable);

	Button->SetSimulatePhysics(false);

	CylinderCollider->OnComponentBeginOverlap.AddDynamic(this, &APressurePlateButton::OnButtonOverlap);
	CylinderCollider->OnComponentEndOverlap.AddDynamic(this, &APressurePlateButton::OnButtonEndOverlap);

	Button->SetAbsolute(false, true, true);
}

// Called when the game starts or when spawned
void APressurePlateButton::BeginPlay()
{
	Super::BeginPlay();
	OriginalButtonPosition = Button->GetComponentLocation();

	ButtonMID = UMaterialInstanceDynamic::Create(ButtonMaterial, this);
	PressedButtonMID = UMaterialInstanceDynamic::Create(PressedButtonMaterial, this);
}

void APressurePlateButton::ChangeLight(bool _bLit)
{
	if (_bLit)
	{
		if (PressedButtonMID) Button->SetMaterial(0, PressedButtonMID);
	}
	else
	{
		if (ButtonMID) Button->SetMaterial(0, ButtonMID);
	}
}

void APressurePlateButton::OverlapDelay()
{
	if (IsOverlapping == false)
	{
		GetWorldTimerManager().ClearTimer(OverlapDelayHandler);
		Button->SetSimulatePhysics(false);
		MoveUp = true;
		if (TriggerActor != nullptr) TriggerActor->DisableTrigger();
		// Disable Sound
		// Turn off light
		ChangeLight(false);
	}
}

void APressurePlateButton::OnButtonOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComp != Plate && OverlappedComp != Button && OtherActor != this)
	{
		NumOnButton++;
		if (NumOnButton > 1) return;
		if (GetWorldTimerManager().TimerExists(OverlapDelayHandler))
		{
			GetWorldTimerManager().ClearTimer(OverlapDelayHandler);
			return;
		}
		Button->SetSimulatePhysics(true);
		IsOverlapping = true;
		MoveUp = false;
		if (TriggerActor != nullptr) TriggerActor->Trigger();
		// Light Up
		ChangeLight(true);
		// Enable sound
	}
}

void APressurePlateButton::OnButtonEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (NumOnButton > 0) NumOnButton--;
	if (NumOnButton > 0) return;
	IsOverlapping = false;
	if (ReturnTime != 0.0f) GetWorldTimerManager().SetTimer(OverlapDelayHandler, this, &APressurePlateButton::OverlapDelay, ReturnTime, false);
	else OverlapDelay();
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

