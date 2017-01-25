// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "InteractActor.h"
#include "HandComponent.h"

UHandComponent::UHandComponent(){

	IsBusy = NULL;
	Nearby = NULL;

	// Create Mesh for Hand
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(this);

	// Create Arrow Component as attach location for objects
	HoldLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Hold Location"));
	HoldLocation->SetupAttachment(this);
}
