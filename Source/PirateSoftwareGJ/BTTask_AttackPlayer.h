// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UBTTask_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_AttackPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory) override;
};
