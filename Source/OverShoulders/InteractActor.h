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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTriggerActionPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTriggerActionReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractGripActionPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractGripActionReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTrackpadActionPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Controls")
		void InteractTrackpardActionReleased();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* DefaultRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Shape;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Hitbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsInteracted;

};
