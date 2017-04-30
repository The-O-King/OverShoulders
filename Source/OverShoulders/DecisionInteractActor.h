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
	
	ADecisionInteractActor();
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelToLoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool RotateText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTextRenderComponent* BaseText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTextRenderComponent* ConsequenceText;

	UFUNCTION()
		void OnOverlapWithHandBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void IsSelected();
	UFUNCTION()
		void DecisionTime();
	UFUNCTION()
		void IsPointedAt();
	UFUNCTION()
		void IsNotPointed();
	UFUNCTION()
		void LevelLoadWrapper();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float levelFadeOutTime;
};
