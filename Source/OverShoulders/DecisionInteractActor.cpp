// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "VR_Pawn.h"
#include "DecisionInteractActor.h"



ADecisionInteractActor::ADecisionInteractActor() {
	BaseText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Base Text"));
	BaseText->SetupAttachment(Shape);
	BaseText->bVisible = false;

	ConsequenceText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Consequence Text"));
	ConsequenceText->SetupAttachment(Shape);
	ConsequenceText->bVisible = false;

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ADecisionInteractActor::OnOverlapWithHandBegin);
}

// Called every frame
void ADecisionInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add Text Rotation to Face the Player always
}


void ADecisionInteractActor::OnOverlapWithHandBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("DecisionActor Overlap Begin with %s"), *OtherActor->GetName());
	AVR_Pawn* hit = Cast<AVR_Pawn>(OtherActor);
	if (hit != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Base Text: %s Consequence Text: %s"), (BaseText->bVisible ? TEXT("True") : TEXT("False")), (ConsequenceText->bVisible ? TEXT("True") : TEXT("False")));
		if (!BaseText->bVisible)
			BaseText->SetVisibility(true);
		else if (!ConsequenceText->bVisible)
			ConsequenceText->SetVisibility(true);
		//else
		    //Start Timer for decision
	}
}

void ADecisionInteractActor::InteractTriggerAxis_Implementation(float AxisValue) {}

void ADecisionInteractActor::InteractTriggerActionPressed_Implementation() {
	UGameplayStatics::OpenLevel(this, LevelToLoad, false);
}

void ADecisionInteractActor::InteractTriggerActionReleased_Implementation() {}
void ADecisionInteractActor::InteractGripActionPressed_Implementation() {}
void ADecisionInteractActor::InteractGripActionReleased_Implementation() {}
void ADecisionInteractActor::InteractTrackpadActionPressed_Implementation() {}
void ADecisionInteractActor::InteractTrackpadActionReleased_Implementation() {}