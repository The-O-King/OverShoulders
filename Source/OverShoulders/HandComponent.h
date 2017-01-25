// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MotionControllerComponent.h"
#include "HandComponent.generated.h"

/**
*
*/
UCLASS()
class OVERSHOULDERS_API UHandComponent : public UMotionControllerComponent
{
	GENERATED_BODY()

public:

	UHandComponent();

	UPROPERTY(VisibleAnywhere)
		class AInteractActor* IsBusy;
	UPROPERTY(VisibleAnywhere)
		class AInteractActor* Nearby;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
		UArrowComponent* HoldLocation;

};
