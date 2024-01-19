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
	if (!IsValid(enemyChar))
		return EBTNodeResult::Failed;

	TMap<APatrolPointActor*, float> patrolPoints = enemyChar->GetPatrolPath();

	if (patrolPoints.IsEmpty())
		return EBTNodeResult::Failed;

	int index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("PatrolIndex"));

	if (patrolPoints.Num() <= index)
	{
		index=0;
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("PatrolIndex"), 0);
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PatrolLoc"), patrolPoints.Array()[index].Key->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("WaitTime"), patrolPoints.Array()[index].Value);
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("PatrolIndex"), index+1);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PatrolFaceLoc"), patrolPoints.Array()[index].Key->GetActorRotation().Vector());

	return EBTNodeResult::Succeeded;
}
