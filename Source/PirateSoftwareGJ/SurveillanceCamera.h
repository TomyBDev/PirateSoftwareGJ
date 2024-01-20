// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurveillanceCamera.generated.h"

class UArrowComponent;

UCLASS()
class PIRATESOFTWAREGJ_API ASurveillanceCamera : public AActor
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

private:

	UPROPERTY(EditAnywhere)
	USceneComponent* rootComp;

	UPROPERTY(EditAnywhere)
	UArrowComponent* arrowComp;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cameraStand;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cameraHead;
	
	UPROPERTY(EditAnywhere)
	class UVisionConeComponent* visionCone;
};
