// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "DrawDebugHelpers.h"
#include "EnemyAIController.h"
#include "VisionConeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


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

	aiController = Cast<AEnemyAIController>(GetController());
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemyCharacter::InvestigateCamera(FVector loc)
{
	visionCone->SetAlertState(EAlertState::ALERT);
	
	if (IsValid(aiController))
		aiController->GetBBComp()->SetValueAsVector(TEXT("LastKnownLocation"), loc);
}

void AEnemyCharacter::InvestigateDistraction(AActor* actor)
{
	visionCone->SetAlertState(EAlertState::ALERT);
	
	if (IsValid(aiController))
		aiController->GetBBComp()->SetValueAsObject(TEXT("Distraction"), actor);
}

void AEnemyCharacter::StartDetection_Implementation(AActor* otherActor)
{
	// Chase Player
	if (IsValid(aiController))
		aiController->GetBBComp()->SetValueAsObject(TEXT("PlayerRef"), otherActor);
}

void AEnemyCharacter::EndDetection_Implementation(AActor* otherActor)
{
	// Lost track of player
	if (IsValid(aiController))
	{
		aiController->GetBBComp()->SetValueAsVector(TEXT("LastKnownLocation"), otherActor->GetActorLocation());
		aiController->GetBBComp()->ClearValue(TEXT("PlayerRef"));
	}
}
