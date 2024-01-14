// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToRandom.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UBTTask_MoveToRandom : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_MoveToRandom();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory) override;
};
