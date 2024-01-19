// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToPatrol.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UBTTask_RotateToPatrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_RotateToPatrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory) override;
};
