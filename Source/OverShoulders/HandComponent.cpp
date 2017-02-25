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
	UE_LOG(LogTemp, Warning, TEXT("%s Overlap Begin with %s"), *OverlappedComp->GetName(), *OtherActor->GetName());
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		Nearby = hit;
	}
}

void UHandComponent::OnHandOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("%s Overlap End with %s"), *OverlappedComp->GetName(), *OtherActor->GetName());
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		if (hit == Nearby) {
			Nearby = NULL;
		}
	}
}

void UHandComponent::TriggerAxisInput_Implementation(float AxisValue){
	if (IsBusy != NULL) {
		IsBusy->InteractTriggerAxis(AxisValue);
	}
	else {
		//Do Animation??
	}
}
void UHandComponent::TriggerActionInputPressed_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("%s Trigger Pressed"), *this->GetName());
	if (IsBusy != NULL) {
		IsBusy->InteractTriggerActionPressed();
	}
	else {
		//Do Animation??
	}
}
void UHandComponent::TriggerActionInputReleased_Implementation() {
	if (IsBusy != NULL) {
		IsBusy->InteractTriggerActionReleased();
	}
	else {
		//Do Animation??
	}
}
void UHandComponent::GripActionInputPressed_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("%s Grip Pressed"), *this->GetName());
	//if (IsBusy != NULL) {
	//	IsBusy->InteractGripActionPressed();
	//}
	//else {
		if (Nearby != NULL) {
			IsBusy = Nearby;
			IsBusy->Shape->SetSimulatePhysics(false);
			IsBusy->AttachToComponent(HoldLocation, FAttachmentTransformRules::KeepWorldTransform);
			IsBusy->IsInteracted = true;
			Nearby = NULL;
		}
		else if (IsBusy != NULL) {
			IsBusy->IsInteracted = false;
			IsBusy->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			IsBusy->Shape->SetSimulatePhysics(true);
			IsBusy = NULL;
		}
		//Do Animation??
	//}
}
void UHandComponent::GripActionInputReleased_Implementation() {
	if (IsBusy != NULL) {
		IsBusy->InteractGripActionReleased();
	}
	else {
		//Do Animation??
	}
}
void UHandComponent::TrackpadActionInputPressed_Implementation() {
	if (IsBusy != NULL) {
		IsBusy->InteractTrackpadActionPressed();
	}
	else {
		//Do Animation??
	}
}
void UHandComponent::TrackpadActionInputReleased_Implementation() {
	if (IsBusy != NULL) {
		IsBusy->InteractTrackpadActionReleased();
	}
	else {
		//Do Animation??
	}
}