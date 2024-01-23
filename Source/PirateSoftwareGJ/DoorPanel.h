// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "DoorPanel.generated.h"

class UWidgetComponent;
class UBoxComponent;

UCLASS()
class PIRATESOFTWAREGJ_API ADoorPanel : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginInteraction_Implementation() override;

	/** End Interaction */
	virtual void EndInteraction_Implementation() override;

	/** Interaction Cancelled */
	virtual void InteractionCancelled_Implementation() override;

	/** Lookat Begin */
	virtual void LookatBegin_Implementation() override;

	/** Lookat End */
	virtual void LookatEnd_Implementation() override;
	

private:

	UPROPERTY(EditAnywhere)
	USceneComponent* rootComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* interactionCollider;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* interactWidget;
	
	UPROPERTY(EditAnywhere)
	class ADoor* linkedDoor;

	class UInteractWidget* interactionWidget;
	
	float percent = 0.f;

	bool bLockInteraction = false;
};
