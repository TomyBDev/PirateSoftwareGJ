// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_EndDistruption.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Distraction.h"

UBTTask_EndDistruption::UBTTask_EndDistruption()
{
	NodeName = TEXT("Clear Node");
}

EBTNodeResult::Type UBTTask_EndDistruption::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	ADistraction* distraction = Cast<ADistraction>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (IsValid(distraction))
		distraction->TurnOff();

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
