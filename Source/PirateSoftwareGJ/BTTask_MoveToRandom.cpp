// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_MoveToRandom.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"

UBTTask_MoveToRandom::UBTTask_MoveToRandom()
{
	NodeName = TEXT("Move To Random");
}

EBTNodeResult::Type UBTTask_MoveToRandom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(OwnerComp, nodeMemory);

	AEnemyCharacter* enemyChar = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	FNavLocation Location;
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navSystem->GetRandomReachablePointInRadius(enemyChar->GetActorLocation(), 1000.f, Location))
	{
		OwnerComp.GetAIOwner()->MoveToLocation(Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}