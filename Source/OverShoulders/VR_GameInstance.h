// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "VR_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OVERSHOULDERS_API UVR_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UVR_GameInstance();

	bool debugMode;	
};
