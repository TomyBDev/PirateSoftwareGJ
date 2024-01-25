// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_ClearNode.h"

#include "AIController.h"
#include "EnemyCharacter.h"
#include "VisionConeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearNode::UBTTask_ClearNode()
{
	NodeName = TEXT("Clear Node");
}

EBTNodeResult::Type UBTTask_ClearNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(enemy))
		return EBTNodeResult::Succeeded;
		
	UVisionConeComponent* visionCone = enemy->GetVisionConeComponent();
	if (IsValid(visionCone))
		visionCone->SetAlertState(0);

	return EBTNodeResult::Succeeded;
}
