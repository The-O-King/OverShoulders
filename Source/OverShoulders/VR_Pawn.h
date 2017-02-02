// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "VR_Pawn.generated.h"

UCLASS()
class OVERSHOULDERS_API AVR_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVR_Pawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* Body;
	UPROPERTY(EditAnywhere)
		USceneComponent* Container;
	UPROPERTY(EditAnywhere)
		UCameraComponent* HMD;
	UPROPERTY(EditAnywhere)
		class UHandComponent* Left;
	UPROPERTY(EditAnywhere)
		class UHandComponent* Right;

		UPROPERTY(EditAnywhere)
		class USteamVRChaperoneComponent* SteamVR;

};
