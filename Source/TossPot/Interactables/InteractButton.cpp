// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractButton.h"
#include "ConstructorHelpers.h"
#include "Engine.h"


// Sets default values
AInteractButton::AInteractButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Button Skeleton Mesh"));
	
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/Models/Interactables/InteractButton/InteractButton.InteractButton'"));

	ButtonMesh->SetSkeletalMesh(MeshObj.Object, true);

	ButtonMesh->SetCollisionProfileName("BlockAll");

	const ConstructorHelpers::FObjectFinder<UAnimSequence> PushAnim(TEXT("AnimSequence'/Game/Models/Interactables/InteractButton/InteractButton_Anim.InteractButton_Anim'"));

	PushAnimation = PushAnim.Object;
	
}

// Called when the game starts or when spawned
void AInteractButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractButton::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("Using Interact Button Interact Function"));
	
	ButtonMesh->PlayAnimation(PushAnimation, false);

	if (TriggerActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Trigger Actor Not set!"));
		return;
	}
	TriggerActor->Trigger();
	if (DelayTime != 0)
	{
		GetWorldTimerManager().SetTimer(DisableTriggerDelay, this, &AInteractButton::DisableTrigger, DelayTime, false);
	}
}

void AInteractButton::DisableTrigger()
{
	TriggerActor->DisableTrigger();
	GetWorldTimerManager().ClearTimer(DisableTriggerDelay);
}