// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearNode.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UBTTask_ClearNode : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ClearNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
