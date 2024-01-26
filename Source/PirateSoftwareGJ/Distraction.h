// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Distraction.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API ADistraction : public AInteractableActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ADistraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TurnOff();

protected:

	virtual bool BeginInteraction_Implementation() override;

	/** End Interaction */
	virtual bool EndInteraction_Implementation() override;

	/** Interaction Cancelled */
	virtual bool InteractionCancelled_Implementation() override;

	/** Lookat Begin */
	virtual bool LookatBegin_Implementation() override;

	/** Lookat End */
	virtual bool LookatEnd_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	USoundBase* distractionSound;

	UAudioComponent* distractionAC;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> enemyActor;

	TArray<AEnemyCharacter*> enemies;
};
