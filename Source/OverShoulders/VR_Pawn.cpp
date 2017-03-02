// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "HeadMountedDisplay.h"
#include "HandComponent.h"
#include "InteractActor.h"
#include "SteamVRChaperoneComponent.h"
#include "VR_Pawn.h"


// Sets default values
AVR_Pawn::AVR_Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseEyeHeight = 0.0f;

	// Create Default Root Object
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	

	// Create the Body of the player in the space
	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BODY"));
	Body->SetCapsuleHalfHeight(96);
	Body->SetCapsuleRadius(16);

	// Create a Scene Object Holder for Camera and Controllers
	Container = CreateDefaultSubobject<USceneComponent>(TEXT("Container"));

	// Create the Camera and subsequent HMD
	HMD = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD"));
	HMD->SetupAttachment(Container);

	// Create the players Left and Right hands
	Left = CreateDefaultSubobject<UHandComponent>(TEXT("Left"));
	Left->SetupAttachment(Container);
	Left->RegisterComponent();
	Left->Hand = EControllerHand::Left;
	MeshL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshL"));
	MeshL->SetupAttachment(Left);

	Right = CreateDefaultSubobject<UHandComponent>(TEXT("Right"));
	Right->SetupAttachment(Container);
	Right->RegisterComponent();
	Right->Hand = EControllerHand::Right;
	MeshR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshR"));
	MeshR->SetupAttachment(Right);

	// Create SteamVR Chaperone
	SteamVR = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("SteamVRChaperoneComponent"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AVR_Pawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVR_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Pawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("GripLeft", IE_Pressed, Left, &UHandComponent::GripActionInputPressed);
	InputComponent->BindAction("GripRight", IE_Pressed, Right, &UHandComponent::GripActionInputPressed);
	InputComponent->BindAction("TriggerLeft", IE_Pressed, Left, &UHandComponent::TriggerActionInputPressed);
	InputComponent->BindAction("TriggerRight", IE_Pressed, Right, &UHandComponent::TriggerActionInputPressed);
}