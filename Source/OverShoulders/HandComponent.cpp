// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "InteractActor.h"
#include "HandComponent.h"
#include "Haptics/HapticFeedbackEffect_Base.h"

UHandComponent::UHandComponent(){

	IsBusy = NULL;
	Nearby = NULL;
	vibrate = NULL;

	// Create Mesh for Hand
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(this);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &UHandComponent::OnHandOverlapBegin);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &UHandComponent::OnHandOverlapEnd);

	// Create Arrow Component as attach location for objects
	HoldLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Hold Location"));
	HoldLocation->SetupAttachment(this);
}

void UHandComponent::TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction){
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);
	//if (vibrate)
	//	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayHapticEffect(LoadObject<class UHapticFeedbackEffect_Base>(NULL, TEXT("/Game/Tests/NewHapticFeedbackEffect_Buffer"), NULL, LOAD_None, NULL), Hand, 1.0f, false);
}

void UHandComponent::OnHandOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	//vibrate = true;
	UE_LOG(LogTemp, Warning, TEXT("%s Overlapped %s"), *OverlappedComp->GetName(), *OtherActor->GetName());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayHapticEffect(LoadObject<class UHapticFeedbackEffect_Base>(NULL, TEXT("/Game/Tests/NewHapticFeedbackEffect_Curve"), NULL, LOAD_None, NULL), Hand, 1.0f, false);
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
		Nearby = hit;
		hit->Shape->SetSimulatePhysics(true);
	}
}

void UHandComponent::OnHandOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
	//vibrate = false;
	UE_LOG(LogTemp, Warning, TEXT("%s Stopped Overlapping %s"), *OverlappedComp->GetName(), *OtherActor->GetName());
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		if (hit == Nearby) {
			UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
			Nearby = NULL;
		}
	}
}