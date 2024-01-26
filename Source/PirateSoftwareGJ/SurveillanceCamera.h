// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "SurveillanceCamera.generated.h"

class UArrowComponent;

UCLASS()
class PIRATESOFTWAREGJ_API ASurveillanceCamera : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASurveillanceCamera();

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
	
private:
	UFUNCTION()
	void TurnCamera();

	void HackOver();

	void PlayerCheck();;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cameraHead;
	
	UPROPERTY(EditAnywhere)
	class UVisionConeComponent* visionCone;

	UPROPERTY(EditAnywhere, Category="Camera Settings")
	float turnRange = 65.f;

	UPROPERTY(EditAnywhere, Category="Camera Settings")
	float turnSpeed = 25.;

	UPROPERTY(EditAnywhere, Category="Camera Settings")
	float turnCooldown = 2.5f;

	UPROPERTY(EditAnywhere, Category="Camera Settings")
	float startAngle = 0.f;

	bool bWaiting = false;
	
	FTimerHandle turnCooldownTH;

	// Disabled Timer

	FTimerHandle disabledTH;

	float disabledTime = 5.f;

	// Detection Loop

	FTimerHandle detectionTH;

	ACharacter* characterRef;
	
};
