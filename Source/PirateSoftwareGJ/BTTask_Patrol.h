// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UBTTask_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory) override;

private:

	void WaitDone();
	
	FTimerHandle waitTH;

	int index = 0;
};
