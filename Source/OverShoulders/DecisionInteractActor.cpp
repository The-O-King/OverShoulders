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

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ADecisionInteractActor::OnOverlapWithHandBegin);
}

// Called every frame
void ADecisionInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add Text Rotation to Face the Player always
	FVector playerHeadLoc = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	FRotator playerHeadRot = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	//if (player != NULL) {
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
	//}
}

void ADecisionInteractActor::OnOverlapWithHandBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("DecisionActor Overlap Begin with %s"), *OtherActor->GetName());
	AVR_Pawn* hit = Cast<AVR_Pawn>(OtherActor);
	if (hit != NULL)
		IsSelected();
}

void ADecisionInteractActor::IsSelected() {
	UE_LOG(LogTemp, Warning, TEXT("Base Text: %s Consequence Text: %s"), (BaseText->bVisible ? TEXT("True") : TEXT("False")), (ConsequenceText->bVisible ? TEXT("True") : TEXT("False")));
	//if (!BaseText->bVisible)
	//	BaseText->SetVisibility(true);
	if (!ConsequenceText->bVisible)
		ConsequenceText->SetVisibility(true);
	else
		UGameplayStatics::OpenLevel(this, LevelToLoad, false);
	//else
	//Start Timer for decision
}

void ADecisionInteractActor::DecisionTime() {
	BaseText->SetVisibility(true);
}

void ADecisionInteractActor::InteractTriggerActionPressed_Implementation() {
	UGameplayStatics::OpenLevel(this, LevelToLoad, false);
}