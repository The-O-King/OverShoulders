// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "InteractActor.h"


// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Default Root Object
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Create Static Mesh of Object
	Shape = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	Shape->SetupAttachment(DefaultRoot);
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

