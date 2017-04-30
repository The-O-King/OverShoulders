// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "VR_Pawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExploreTimer);

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

	// Wrapper for Broadcast of ExploreTimer
	void ExploreTimeUp();

	// What to do when DecisionTime has completed
	void DecisionTimeUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCapsuleComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* Container;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* HMD;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTextRenderComponent* DecisionText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UWidgetComponent* Timer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UHandComponent* Left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* MeshL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UHandComponent* Right;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* MeshR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USteamVRChaperoneComponent* SteamVR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float expTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float decTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float levelFadeInTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTimerHandle GameTimerHandle;

	FExploreTimer ExploreTimer_Complete;
};
