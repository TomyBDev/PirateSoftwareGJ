// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "DrawDebugHelpers.h"
#include "EnemyAIController.h"
#include "VisionConeComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	visionCone = CreateDefaultSubobject<UVisionConeComponent>(TEXT("Vision Cone Component"));
	AddOwnedComponent(visionCone);
	visionCone->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemyCharacter::InvestigateCamera(FVector loc)
{
	visionCone->SetAlertState(EAlertState::ALERT);
	
	AEnemyAIController* aiController = Cast<AEnemyAIController>(GetController());
	if (IsValid(aiController))
		aiController->SetBBVec(TEXT("LastKnownLocation"), loc);
}

void AEnemyCharacter::InvestigateDistraction(AActor* actor)
{
	visionCone->SetAlertState(EAlertState::ALERT);
	
	AEnemyAIController* aiController = Cast<AEnemyAIController>(GetController());
	if (IsValid(aiController))
		aiController->SetBBObj(TEXT("Distraction"), actor);
	
}
