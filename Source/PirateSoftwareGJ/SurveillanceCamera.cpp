// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "SurveillanceCamera.h"

#include "VisionConeComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ASurveillanceCamera::ASurveillanceCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	RootComponent = rootComp;

	arrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Comp"));
	arrowComp->SetupAttachment(rootComp);
	
	cameraStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera Stand Static Mesh"));
	cameraStand->SetupAttachment(rootComp);

	cameraHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera Head Static Mesh"));
	cameraHead->SetupAttachment(cameraStand);
	
	visionCone = CreateDefaultSubobject<UVisionConeComponent>(TEXT("Vision Cone Component"));
	AddOwnedComponent(visionCone);
	visionCone->AttachToComponent(cameraHead, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ASurveillanceCamera::BeginPlay()
{
	Super::BeginPlay();

	startRot = FRotator(0,-turnRange,0);
	targetRot = FRotator(0,turnRange,0);
}

// Called every frame
void ASurveillanceCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWaiting)
		return;

	if(cameraHead->GetRelativeRotation().Equals(targetRot, 1.f))
	{
		GetWorld()->GetTimerManager().SetTimer(turnCooldownTH, this, &ASurveillanceCamera::TurnCamera, turnCooldown, false);
		bWaiting = true;
		return;
	}
	
	cameraHead->SetRelativeRotation(FMath::RInterpConstantTo(cameraHead->GetRelativeRotation(), cameraHead->GetRelativeRotation() + targetRot, DeltaTime, turnSpeed));
	
}

void ASurveillanceCamera::TurnCamera()
{
	/*FRotator temp = startRot;
	startRot = targetRot;
	targetRot = temp;*/

	targetRot.Yaw *= -1;
	bWaiting = false;
}

