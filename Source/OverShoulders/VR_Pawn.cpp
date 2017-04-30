// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "HeadMountedDisplay.h"
#include "HandComponent.h"
#include "InteractActor.h"
#include "DecisionInteractActor.h"
#include "WidgetComponent.h"
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

	// Create the Timer and Decision Text
	Timer = CreateDefaultSubobject<UWidgetComponent>(TEXT("Timer"));
	Timer->SetupAttachment(HMD);
	Timer->SetVisibility(false);
	DecisionText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Decision Text"));
	DecisionText->SetupAttachment(HMD);
	DecisionText->SetVisibility(false);

	// Create the players Left and Right hands
	Left = CreateDefaultSubobject<UHandComponent>(TEXT("Left"));
	Left->SetupAttachment(Container);
	//Left->RegisterComponent();
	Left->Hand = EControllerHand::Left;
	MeshL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshL"));
	MeshL->SetupAttachment(Left);
	MeshL->OnComponentBeginOverlap.AddDynamic(Left, &UHandComponent::OnHandOverlapBegin);
	MeshL->OnComponentEndOverlap.AddDynamic(Left, &UHandComponent::OnHandOverlapEnd);

	Right = CreateDefaultSubobject<UHandComponent>(TEXT("Right"));
	Right->SetupAttachment(Container);
	//Right->RegisterComponent();
	Right->Hand = EControllerHand::Right;
	MeshR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshR"));
	MeshR->SetupAttachment(Right);
	MeshR->OnComponentBeginOverlap.AddDynamic(Right, &UHandComponent::OnHandOverlapBegin);
	MeshR->OnComponentEndOverlap.AddDynamic(Right, &UHandComponent::OnHandOverlapEnd);

	// Create SteamVR Chaperone
	SteamVR = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("SteamVRChaperoneComponent"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	expTime = 10;
	decTime = 10;
	levelFadeInTime = 15;
}

// Called when the game starts or when spawned
void AVR_Pawn::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1, 0, levelFadeInTime, FLinearColor::Black, false, true);
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AVR_Pawn::ExploreTimeUp, expTime, false);
}

// Called every frame
void AVR_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVR_Pawn::ExploreTimeUp() {
	UE_LOG(LogTemp, Warning, TEXT("Explore Time Is Up"));
	ExploreTimer_Complete.Broadcast();
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AVR_Pawn::DecisionTimeUp, decTime, false);
	Timer->SetVisibility(true);
	DecisionText->SetVisibility(true);
}

void AVR_Pawn::DecisionTimeUp() {
	TActorIterator<ADecisionInteractActor> ActorItr(GetWorld());
	int num = rand() % 2;
	for (int x = 0; x < num; x++)
		++ActorItr;
	if (*ActorItr != NULL)
		ActorItr->IsSelected();
}

// Called to bind functionality to input
void AVR_Pawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("GripLeft", IE_Pressed, Left, &UHandComponent::GripActionInputPressed);
	InputComponent->BindAction("GripRight", IE_Pressed, Right, &UHandComponent::GripActionInputPressed);
	InputComponent->BindAction("TriggerLeft", IE_Pressed, Left, &UHandComponent::TriggerActionInputPressed);
	InputComponent->BindAction("TriggerRight", IE_Pressed, Right, &UHandComponent::TriggerActionInputPressed);
	InputComponent->BindAction("TriggerLeft", IE_Released, Left, &UHandComponent::TriggerActionInputReleased);
	InputComponent->BindAction("TriggerRight", IE_Released, Right, &UHandComponent::TriggerActionInputReleased);
	InputComponent->BindAction("TrackpadLeft", IE_Pressed, Left, &UHandComponent::TrackpadActionInputPressed);
	InputComponent->BindAction("TrackpadRight", IE_Pressed, Right, &UHandComponent::TrackpadActionInputPressed);

}