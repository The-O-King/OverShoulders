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

	UFUNCTION()
	void OnHandOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHandOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere)
		class AInteractActor* IsBusy;
	UPROPERTY(EditAnywhere)
		class AInteractActor* Nearby;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		UArrowComponent* HoldLocation;

};
