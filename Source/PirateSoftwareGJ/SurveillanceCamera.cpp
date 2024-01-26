// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "SurveillanceCamera.h"

#include "InteractWidget.h"
#include "VisionConeComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	characterRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	GetWorld()->GetTimerManager().SetTimer(detectionTH, this, &ASurveillanceCamera::PlayerCheck, 0.166f, true);

	cameraHead->SetRelativeRotation(FRotator(0.0f, startAngle, 0.0f));
}

// Called every frame
void ASurveillanceCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWaiting)
		return;

	if(cameraHead->GetRelativeRotation().Yaw > startAngle + turnRange )
	{
		cameraHead->SetRelativeRotation(FRotator(0,startAngle+turnRange-0.1f,0));
		GetWorld()->GetTimerManager().SetTimer(turnCooldownTH, this, &ASurveillanceCamera::TurnCamera, turnCooldown, false);
		bWaiting = true;
		return;
	}
	if (cameraHead->GetRelativeRotation().Yaw < startAngle - turnRange)
	{
		cameraHead->SetRelativeRotation(FRotator(0,startAngle-turnRange+0.1f,0));
		GetWorld()->GetTimerManager().SetTimer(turnCooldownTH, this, &ASurveillanceCamera::TurnCamera, turnCooldown, false);
		bWaiting = true;
		return;
	}
	
	cameraHead->AddRelativeRotation(FRotator(0.f,DeltaTime*turnSpeed, 0.f));
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
	turnSpeed *= -1;
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

void ASurveillanceCamera::PlayerCheck()
{
	if (IsValid(characterRef) && FVector::Dist(characterRef->GetActorLocation(), visionCone->GetComponentLocation()) < visionCone->GetRange())
	{
		float thing1 = abs(cameraHead->GetForwardVector().Dot(UKismetMathLibrary::GetDirectionUnitVector(visionCone->GetComponentLocation(),characterRef->GetActorLocation())));
		float thing2 = visionCone->GetAngle() / 90.f;
	
		if (thing1 < thing2)
		{
			visionCone->SetAlertState(2);
			return;
		}
	}

	visionCone->SetAlertState(0);
}

