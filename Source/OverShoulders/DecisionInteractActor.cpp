// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "DecisionInteractActor.h"





void ADecisionInteractActor::InteractTriggerAxis_Implementation(float AxisValue) {}

void ADecisionInteractActor::InteractTriggerActionPressed_Implementation() {
	UGameplayStatics::OpenLevel(this, LevelToLoad, false);
}

void ADecisionInteractActor::InteractTriggerActionReleased_Implementation() {}
void ADecisionInteractActor::InteractGripActionPressed_Implementation() {}
void ADecisionInteractActor::InteractGripActionReleased_Implementation() {}
void ADecisionInteractActor::InteractTrackpadActionPressed_Implementation() {}
void ADecisionInteractActor::InteractTrackpadActionReleased_Implementation() {}