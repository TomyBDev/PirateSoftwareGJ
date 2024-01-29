// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "RealtimeMeshComponent.h"
#include "Mesh/RealtimeMeshSimpleData.h"
#include "VisionConeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATESOFTWAREGJ_API UVisionConeComponent : public URealtimeMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVisionConeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetAlertState(int state);

	float GetRange() const { return distance; }
	
	float GetAngle() const { return angle; }

private:
	
	TArray<FVector> GetPoints();

	void AppendTriangleMesh(struct FRealtimeMeshSimpleMeshData& MeshData, TArray<FVector> Points, int32 NewMaterialGroup);
	
	struct FRealtimeMeshSectionConfig OnAddSectionToPolyGroup(int32 PolyGroupIndex);
	
	UPROPERTY(EditAnywhere, Category="Vision Cone")
	UMaterialInterface* visionConeMat;
	
	UPROPERTY(EditAnywhere, Category="Vision Cone")
	UMaterialInterface* visionConeAlertMat;
	
	UPROPERTY(EditAnywhere, Category="Vision Cone")
	UMaterialInterface* visionConeChaseMat;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	int resolution = 12;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float distance = 200.f;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float angle = 45.f;

	FRealtimeMeshSimpleMeshData meshData;
	
	FRealtimeMeshSectionGroupKey SectionGroupKey;

	class URealtimeMeshSimple* RealtimeMesh;
};
