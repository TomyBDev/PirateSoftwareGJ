// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "SurveillanceCamera.h"

#include "InteractWidget.h"
#include "VisionConeComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

#define COLLISION_INTERACTION ECC_GameTraceChannel1

// Sets default values
ASurveillanceCamera::ASurveillanceCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera Head Static Mesh"));
	cameraHead->SetupAttachment(mesh);
	
	visionCone = CreateDefaultSubobject<UVisionConeComponent>(TEXT("Vision Cone Component"));
	AddOwnedComponent(visionCone);
	visionCone->AttachToComponent(cameraHead, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ASurveillanceCamera::BeginPlay()
{
	Super::BeginPlay();
	
	targetRot = FRotator(0,turnRange,0);
}

// Called every frame
void ASurveillanceCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWaiting)
		return;

	if(cameraHead->GetRelativeRotation().Yaw > turnRange )
	{
		cameraHead->SetRelativeRotation(FRotator(0,turnRange-1,0));
		GetWorld()->GetTimerManager().SetTimer(turnCooldownTH, this, &ASurveillanceCamera::TurnCamera, turnCooldown, false);
		bWaiting = true;
		return;
	}
	if (cameraHead->GetRelativeRotation().Yaw < -turnRange)
	{
		cameraHead->SetRelativeRotation(FRotator(0,-turnRange+1,0));
		GetWorld()->GetTimerManager().SetTimer(turnCooldownTH, this, &ASurveillanceCamera::TurnCamera, turnCooldown, false);
		bWaiting = true;
		return;
	}
	
	cameraHead->SetRelativeRotation(FMath::RInterpConstantTo(cameraHead->GetRelativeRotation(), cameraHead->GetRelativeRotation() + targetRot, DeltaTime, turnSpeed));
	
}

bool ASurveillanceCamera::BeginInteraction_Implementation()
{
	if (Super::BeginInteraction_Implementation())
		return true;

	return false;
}

bool ASurveillanceCamera::EndInteraction_Implementation()
{
	if (Super::EndInteraction_Implementation())
		return true;
	
	visionCone->SetHiddenInGame(true);
	SetActorTickEnabled(false);

	GetWorld()->GetTimerManager().SetTimer(disabledTH, this, &ASurveillanceCamera::HackOver, disabledTime);

	return false;
}

bool ASurveillanceCamera::InteractionCancelled_Implementation()
{
	if (Super::InteractionCancelled_Implementation())
		return true;

	return false;
	
}

bool ASurveillanceCamera::LookatBegin_Implementation()
{
	if (Super::LookatBegin_Implementation())
		return true;

	return false;
	
}

bool ASurveillanceCamera::LookatEnd_Implementation()
{
	if (Super::LookatEnd_Implementation())
		return true;

	return false;
	
}

void ASurveillanceCamera::TurnCamera()
{
	targetRot.Yaw *= -1;
	bWaiting = false;
}

void ASurveillanceCamera::HackOver()
{
	visionCone->SetHiddenInGame(false);
	SetActorTickEnabled(true);

	if (IsValid(interactionWidget))
	{
		interactionWidget->ZeroPercentage();
		interactionWidget->SetComplete(false);
	}
		

	bLockInteraction = false;
}

