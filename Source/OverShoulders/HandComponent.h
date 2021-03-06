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

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	UFUNCTION()
	void OnHandOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHandOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void ClearHands();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Controls")
		void TriggerAxisInput(float AxisValue);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void TriggerActionInputPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void TriggerActionInputReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void GripActionInputPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void GripActionInputReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void TrackpadActionInputPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void TrackpadActionInputReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void MenuActionInputPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class AInteractActor* IsBusy;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class AInteractActor* Nearby;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ADecisionInteractActor* PointedTo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isPointing;
};
