// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

struct FAIStimulus;
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

	virtual void OnPossess(APawn* InPawn) override;
	
public:
	/** Run every frame. */
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const stimulus);
	
private:
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* perceptionComp;

	UPROPERTY(EditAnywhere)
	class UAISenseConfig_Sight* sightConfig;
	
};
