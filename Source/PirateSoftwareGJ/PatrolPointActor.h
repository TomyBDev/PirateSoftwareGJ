// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPointActor.generated.h"

class UArrowComponent;

UCLASS()
class PIRATESOFTWAREGJ_API APatrolPointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* sceneComp;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* arrowComp;
	
};
