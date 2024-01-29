// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "BTTask_AttackPlayer.h"

#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
	NodeName = TEXT("Move To Random");
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(OwnerComp, nodeMemory);
	
	APlayerCharacter* playerChar = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PlayerRef")));
	if (IsValid(playerChar))
		playerChar->HitPlayer();

	return EBTNodeResult::Succeeded;
}
