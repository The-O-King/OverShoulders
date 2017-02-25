// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractActor.h"
#include "DecisionInteractActor.generated.h"

/**
 * 
 */
UCLASS()
class OVERSHOULDERS_API ADecisionInteractActor : public AInteractActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelToLoad;

	//All of these functions are already labeled as BlueprintsNativeEvents in Parent Class
	virtual void InteractTriggerAxis_Implementation(float AxisValue) override;
	virtual void InteractTriggerActionPressed_Implementation() override;
	virtual void InteractTriggerActionReleased_Implementation() override;
	virtual void InteractGripActionPressed_Implementation() override;
	virtual void InteractGripActionReleased_Implementation() override;
	virtual void InteractTrackpadActionPressed_Implementation() override;
	virtual void InteractTrackpadActionReleased_Implementation() override;
	
	
};
