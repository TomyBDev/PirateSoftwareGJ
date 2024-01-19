// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_RotateToPatrol.h"

#include "EnemyCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPointActor.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_RotateToPatrol::UBTTask_RotateToPatrol()
{
	NodeName = TEXT("Rotate To Patrol");
}

EBTNodeResult::Type UBTTask_RotateToPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(OwnerComp, nodeMemory);

	AEnemyCharacter* enemyChar = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(enemyChar))
		return EBTNodeResult::Failed;

	TMap<APatrolPointActor*, float> patrolPoints = enemyChar->GetPatrolPath();
	
	int index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("PatrolIndex"))-1;

	
	return EBTNodeResult::Succeeded;
}
