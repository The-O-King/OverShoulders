// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "OverShouldersGameModeBase.generated.h"

/**
*
*/
UCLASS()
class OVERSHOULDERS_API AOverShouldersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOverShouldersGameModeBase();

	virtual void BeginPlay() override;


};
