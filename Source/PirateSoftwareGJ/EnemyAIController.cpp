// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	/** Check if pointer to behavior tree has been supplied in BP. */
	if (AIBehavior == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SET THE Behavior Tree!!!!"));
		return;
	}

	/** Starts running the behavior tree. */
	RunBehaviorTree(AIBehavior);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIController::SetBBObj(FName bbName, AActor* actor)
{
	GetBlackboardComponent()->SetValueAsObject(bbName, actor);
}

void AEnemyAIController::SetBBVec(FName bbName, FVector vec)
{
	GetBlackboardComponent()->SetValueAsVector(bbName, vec);
}

void AEnemyAIController::StartDetection_Implementation(AActor* otherActor)
{
	// Chase Player
	GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerRef"), otherActor);
}

void AEnemyAIController::EndDetection_Implementation(AActor* otherActor)
{
	// Lost track of player
	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), otherActor->GetActorLocation());
	GetBlackboardComponent()->ClearValue(TEXT("PlayerRef"));
}
