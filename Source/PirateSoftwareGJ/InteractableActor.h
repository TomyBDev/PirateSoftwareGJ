// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

#define COLLISION_INTERACTION ECC_GameTraceChannel1

class UBoxComponent;

UCLASS()
class PIRATESOFTWAREGJ_API AInteractableActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	class UInteractWidget* interactionWidget;
	
	bool bLockInteraction = false;
	
private:

	void IncrementPercent();

	UPROPERTY(EditAnywhere)
	USceneComponent* rootComp;

	UPROPERTY(EditAnywhere)
	UBoxComponent* interactionCollider;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* interactWidget;

	FTimerHandle incrementTH;
};
