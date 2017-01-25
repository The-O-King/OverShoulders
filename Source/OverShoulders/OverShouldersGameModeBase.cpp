// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "VR_Pawn.h"
#include "OverShouldersGameModeBase.h"


AOverShouldersGameModeBase::AOverShouldersGameModeBase() {
	DefaultPawnClass = AVR_Pawn::StaticClass();
}

void AOverShouldersGameModeBase::BeginPlay() {
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
}

