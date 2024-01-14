// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_Patrol.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "PatrolPointActor.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(OwnerComp, nodeMemory);

	AEnemyCharacter* enemyChar = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	TMap<class APatrolPointActor*, float> patrolPoints = enemyChar->GetPatrolPath();

	if (patrolPoints.Num() >= index)
		return EBTNodeResult::Succeeded;
	
		OwnerComp.GetAIOwner()->MoveToLocation(patrolPoint.Key->GetActorLocation());

		GetWorld()->GetTimerManager().SetTimer(waitTH, this, &UBTTask_Patrol::WaitDone, patrolPoint.Value);
	
	
	
}

void UBTTask_Patrol::WaitDone()
{
	
}
