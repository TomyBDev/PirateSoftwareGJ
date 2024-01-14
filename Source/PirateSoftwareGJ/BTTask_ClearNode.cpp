// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_ClearNode.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearNode::UBTTask_ClearNode()
{
	NodeName = TEXT("Clear Node");
}

EBTNodeResult::Type UBTTask_ClearNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
