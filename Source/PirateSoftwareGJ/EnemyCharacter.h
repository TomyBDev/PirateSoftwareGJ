// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class URealtimeMeshComponent;

UCLASS()
class PIRATESOFTWAREGJ_API AEnemyCharacter : public ACharacter
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
	
	TMap<class APatrolPointActor*, float> GetPatrolPath() const {return patrolPath;}

private:

	TArray<FVector> GetPoints();

	void AppendTriangleMesh(struct FRealtimeMeshSimpleMeshData& MeshData, TArray<FVector> Points, int32 NewMaterialGroup);
	
	struct FRealtimeMeshSectionConfig OnAddSectionToPolyGroup(int32 PolyGroupIndex);
	
	UPROPERTY(EditAnywhere)
	class URealtimeMeshComponent* realtimeMeshComponent;
	
	UPROPERTY(EditAnywhere)
	TMap<class APatrolPointActor*, float> patrolPath;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	int resolution = 12;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float distance = 200.f;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float angle = 45.f;
};
