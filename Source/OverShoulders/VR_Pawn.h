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

	void OnHandOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnHandOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(VisibleAnywhere)
		USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* Body;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Container;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* HMD;
	UPROPERTY(VisibleAnywhere)
		class UHandComponent* Left;
	UPROPERTY(VisibleAnywhere)
		class UHandComponent* Right;

		UPROPERTY(VisibleAnywhere)
		class USteamVRChaperoneComponent* SteamVR;

};
