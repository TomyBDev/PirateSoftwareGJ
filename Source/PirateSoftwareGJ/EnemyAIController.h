// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetectionInterface.h"
#include "EnemyAIController.generated.h"

struct FAIStimulus;
/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API AEnemyAIController : public AAIController, public IDetectionInterface
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

	UBlackboardComponent* GetBBComp() { return GetBlackboardComponent(); };

	void SetBBVec(FName bbName, FVector vec);

protected:

	/** Detection Interface. */

	virtual void StartDetection_Implementation(AActor* otherActor) override;

	virtual void EndDetection_Implementation(AActor* otherActor) override;
	
private:

	/** AI. */
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	/** Misc. */

	APlayerCharacter* playerRef;
};
