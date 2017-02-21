// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "InteractActor.h"
#include "HandComponent.h"

UHandComponent::UHandComponent(){

	IsBusy = NULL;
	Nearby = NULL;

	// Create Mesh for Hand
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(this);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &UHandComponent::OnHandOverlapBegin);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &UHandComponent::OnHandOverlapEnd);

	// Create Arrow Component as attach location for objects
	HoldLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Hold Location"));
	HoldLocation->SetupAttachment(this);
}

void UHandComponent::OnHandOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
		Nearby = hit;
	}
}

void UHandComponent::OnHandOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		if (hit == Nearby) {
			UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
			Nearby = NULL;
		}
	}
}

void UHandComponent::TriggerAxisInput_Implementation(float AxisValue){}
void UHandComponent::TriggerActionInputPressed_Implementation() {}
void UHandComponent::TriggerActionInputReleased_Implementation() {}
void UHandComponent::GripActionInputPressed_Implementation() {}
void UHandComponent::GripActionInputReleased_Implementation() {}
void UHandComponent::TrackpadActionInputPressed_Implementation() {}
void UHandComponent::TrackpadActionInputReleased_Implementation() {}