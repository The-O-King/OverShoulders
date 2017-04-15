// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "VR_Pawn.h"
#include "InteractActor.h"
#include "DecisionInteractActor.h"
#include "HandComponent.h"

UHandComponent::UHandComponent(){

	IsBusy = NULL;
	Nearby = NULL;
	PointedTo = NULL;
	isPointing = false;
}


void UHandComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (isPointing) {
		FHitResult hitinfo;
		GetWorld()->LineTraceSingleByChannel(hitinfo, GetComponentLocation(), GetComponentLocation() + GetComponentRotation().Vector() * 256, ECollisionChannel::ECC_WorldDynamic);
		if (hitinfo.GetActor() != NULL) {
			UE_LOG(LogTemp, Warning, TEXT("Pointing at: %s"), *(hitinfo.GetActor())->GetName());
			ADecisionInteractActor* test = Cast<ADecisionInteractActor>(hitinfo.GetActor());
			if (test != NULL)
				PointedTo = test;
		}
	}

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

void UHandComponent::ClearHands() {
	AVR_Pawn* pl = Cast<AVR_Pawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	pl->Left->IsBusy = NULL;
	pl->Right->IsBusy = NULL;
}

void UHandComponent::TriggerActionInputPressed_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("%s Trigger Pressed"), *this->GetName());
	isPointing = true;	
}
void UHandComponent::TriggerActionInputReleased_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("%s Trigger Released"), *this->GetName());
	isPointing = false;
}
void UHandComponent::GripActionInputPressed_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("%s Grip Pressed"), *this->GetName());
	if (Nearby != NULL && Nearby->isPickupable) {
		ClearHands();
		IsBusy = Nearby;
		IsBusy->Shape->SetSimulatePhysics(false);
		IsBusy->AttachToComponent(GetChildComponent(0), FAttachmentTransformRules::KeepWorldTransform);
		IsBusy->IsInteracted = true;
		Nearby = NULL;
	}
	else if (IsBusy != NULL) {
		IsBusy->IsInteracted = false;
		IsBusy->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		IsBusy->Shape->SetSimulatePhysics(true);
		IsBusy = NULL;
	}
}

void UHandComponent::TrackpadActionInputPressed_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("%s Trackpad Pressed"), *this->GetName());
	if (PointedTo != NULL)
		PointedTo->IsSelected();
}

void UHandComponent::TriggerAxisInput_Implementation(float AxisValue) { }
void UHandComponent::GripActionInputReleased_Implementation() { }
void UHandComponent::TrackpadActionInputReleased_Implementation() { }