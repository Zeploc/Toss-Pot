// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractOverlap.h"
#include "Engine.h"



AInteractOverlap::AInteractOverlap()
{

	OverlapColliderBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box Collide"));
	OverlapColliderBox->bGenerateOverlapEvents = true;
	OverlapColliderBox->SetCollisionProfileName("OverlapAll");
	OverlapColliderBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	OverlapColliderBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractOverlap::OnOverlapBegin);
	OverlapColliderBox->OnComponentEndOverlap.AddDynamic(this, &AInteractOverlap::OnOverlapEnd);
}
void AInteractOverlap::Tick(float DeltaTime)
{

}
void AInteractOverlap::BeginPlay()
{
	Super::BeginPlay();

}

void AInteractOverlap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerActor != nullptr) TriggerActor->Trigger();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Trigger Actor"));
}

void AInteractOverlap::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (TriggerActor != nullptr) TriggerActor->DisableTrigger();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Disable Trigger Actor"));
}



