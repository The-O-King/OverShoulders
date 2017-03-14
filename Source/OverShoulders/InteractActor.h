// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractActor.generated.h"

UCLASS()
class OVERSHOULDERS_API AInteractActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTriggerAxis(float AxisValue);
	virtual void InteractTriggerAxis_Implementation(float AxisValue);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTriggerActionPressed();
	virtual void InteractTriggerActionPressed_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTriggerActionReleased();
	virtual void InteractTriggerActionReleased_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractGripActionPressed();
	virtual void InteractGripActionPressed_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractGripActionReleased();
	virtual void InteractGripActionReleased_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTrackpadActionPressed();
	virtual void InteractTrackpadActionPressed_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTrackpadActionReleased();
	virtual void InteractTrackpadActionReleased_Implementation();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Shape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* Hitbox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsInteracted;

};
