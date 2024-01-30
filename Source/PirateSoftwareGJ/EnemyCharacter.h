// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "DetectionInterface.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AEnemyAIController;
class ADistraction;
class URealtimeMeshComponent;

UCLASS()
class PIRATESOFTWAREGJ_API AEnemyCharacter : public ACharacter, public IDetectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	TMap<class APatrolPointActor*, float> GetPatrolPath() const { return patrolPath; }

	class UVisionConeComponent* GetVisionConeComponent() const { return visionCone; }

	void InvestigateCamera(FVector loc);

	void InvestigateDistraction(AActor* actor);

	
protected:
	
	/** Detection Interface. */

	virtual void StartDetection_Implementation(AActor* otherActor) override;

	virtual void EndDetection_Implementation(AActor* otherActor) override;
	
private:
	
	UPROPERTY(EditAnywhere)
	TMap<class APatrolPointActor*, float> patrolPath;

	UPROPERTY(EditAnywhere)
	UVisionConeComponent* visionCone;

	AEnemyAIController* aiController;
};
