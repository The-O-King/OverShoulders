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

	Left = CreateDefaultSubobject<UHandComponent>(TEXT("Left"));
	Left->SetupAttachment(Container);
	Left->RegisterComponent();
	Left->Hand = EControllerHand::Left;
	Left->Mesh->SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Game/VR_Controller"), NULL, LOAD_None, NULL));
	Left->Mesh->Rename(TEXT("Left Mesh"));
	Left->HoldLocation->Rename(TEXT("Left Hold Loc"));
	//Should be mesh or handcomponent still unsure...
	Left->OnComponentBeginOverlap.AddDynamic(this, &AVR_Pawn::OnHandOverlapBegin);
	Left->OnComponentEndOverlap.AddDynamic(this, &AVR_Pawn::OnHandOverlapEnd);

	Right = CreateDefaultSubobject<UHandComponent>(TEXT("Right"));
	Right->SetupAttachment(Container);
	Right->RegisterComponent();
	Right->Hand = EControllerHand::Right;
	Right->Mesh->SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Game/VR_Controller"), NULL, LOAD_None, NULL));
	Right->Mesh->Rename(TEXT("Right Mesh"));
	Right->HoldLocation->Rename(TEXT("Right Hold Loc"));
	//Should be mesh or handcomponent still unsure...
	Right->OnComponentBeginOverlap.AddDynamic(this, &AVR_Pawn::OnHandOverlapBegin);
	Right->OnComponentEndOverlap.AddDynamic(this, &AVR_Pawn::OnHandOverlapEnd);

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

}

void AVR_Pawn::OnHandOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AInteractActor* hit = Cast<AInteractActor>(OtherActor);
	if (hit != NULL) {
		//Should be mesh or should me handcomponent?
		UHandComponent* overlappedHand = Cast<UHandComponent>(OverlappedComp);
		overlappedHand->Nearby = hit;
	}
}

void AVR_Pawn::OnHandOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	UHandComponent* overlappedHand = Cast<UHandComponent>(OverlappedComp);
	overlappedHand->Nearby = NULL;
}