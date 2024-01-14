// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AEnemyAIController();

protected:
	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

public:
	/** Run every frame. */
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
	
};
