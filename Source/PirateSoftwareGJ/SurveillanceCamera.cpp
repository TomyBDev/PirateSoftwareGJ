// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "SurveillanceCamera.h"

#include "EnemyCharacter.h"
#include "InteractWidget.h"
#include "PlayerCharacter.h"
#include "VisionConeComponent.h"
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

	cameraHead->SetRelativeRotation(FRotator(0.0f, startAngle, 0.0f));

	TArray<AActor*> actors;

	if (IsValid(enemyActor))
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), enemyActor, actors);

	for (const auto a : actors)
	{
		enemies.Push(Cast<AEnemyCharacter>(a));
	}
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

void ASurveillanceCamera::StartDetection_Implementation(AActor* otherActor)
{
	for (AEnemyCharacter* e : enemies)
	{ // TODO pass player location.
		e->InvestigateCamera(FVector(0,0,0));
	}

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Camera Sees Player!"));
}

void ASurveillanceCamera::EndDetection_Implementation(AActor* otherActor)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Camera can no longer See Player!"));
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