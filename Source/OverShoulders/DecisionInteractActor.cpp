// Fill out your copyright notice in the Description page of Project Settings.

#include "OverShoulders.h"
#include "VR_Pawn.h"
#include "DecisionInteractActor.h"



ADecisionInteractActor::ADecisionInteractActor() {
	BaseText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Base Text"));
	BaseText->SetupAttachment(Shape);
	BaseText->bVisible = false;

	ConsequenceText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Consequence Text"));
	ConsequenceText->SetupAttachment(Shape);
	ConsequenceText->bVisible = false;

	RotateText = true;
	levelFadeOutTime = 5;
	IsEnding = false;

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ADecisionInteractActor::OnOverlapWithHandBegin);
}

void ADecisionInteractActor::BeginPlay() {
	Super::BeginPlay();

	AVR_Pawn* pl = Cast<AVR_Pawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	pl->ExploreTimer_Complete.AddDynamic(this, &ADecisionInteractActor::DecisionTime);
}

// Called every frame
void ADecisionInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add Text Rotation to Face the Player always
	FVector playerHeadLoc = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	FRotator playerHeadRot = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	if (RotateText) {
		FRotator newrot = (playerHeadLoc - BaseText->GetComponentLocation()).Rotation();
		if (BaseText->bVisible)
			BaseText->SetWorldRotation(newrot);
		if (ConsequenceText->bVisible) {
			//FHitResult hitinfo;
			//GetWorld()->LineTraceSingleByChannel(hitinfo, playerHeadLoc, playerHeadLoc + playerHeadRot.Vector() * 256, ECollisionChannel::ECC_WorldDynamic);
			//ConsequenceText->SetWorldLocation(hitinfo.ImpactPoint);
			//ConsequenceText->SetWorldLocation(ConsequenceText->GetComponentLocation().RotateAngleAxis(1, GetRootComponent()->GetComponentLocation().UpVector));
			ConsequenceText->SetWorldRotation(newrot);
		}
	}
}

void ADecisionInteractActor::OnOverlapWithHandBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("DecisionActor Overlap Begin with %s"), *OtherActor->GetName());
	//AVR_Pawn* hit = Cast<AVR_Pawn>(OtherActor);
	//if (hit != NULL)
	//	IsSelected();
}

void ADecisionInteractActor::IsPointedAt() {
	if (!ConsequenceText->bVisible && BaseText->bVisible)
		ConsequenceText->SetVisibility(true);
}

void ADecisionInteractActor::IsNotPointed() {
	ConsequenceText->SetVisibility(false);
}

void ADecisionInteractActor::IsSelected() {
	FTimerHandle UnusedHandle;
	UE_LOG(LogTemp, Warning, TEXT("Selected: %s"), *GetName());
	if (BaseText->bVisible && !IsEnding) {
		IsEnding = true;
		GetWorldTimerManager().ClearAllTimersForObject(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0, 1, levelFadeOutTime, FLinearColor::Black, true, true);
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADecisionInteractActor::LevelLoadWrapper, levelFadeOutTime + 1, false);
	}
}

void ADecisionInteractActor::LevelLoadWrapper() {
	UGameplayStatics::OpenLevel(this, LevelToLoad, false);
}

void ADecisionInteractActor::DecisionTime() {
	BaseText->SetVisibility(true);
}