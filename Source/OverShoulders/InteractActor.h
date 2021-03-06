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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Shape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* Hitbox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsInteracted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isPickupable;

};
