// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "RealtimeMeshComponent.h"
#include "Mesh/RealtimeMeshSimpleData.h"
#include "VisionConeComponent.generated.h"


enum class EAlertState : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATESOFTWAREGJ_API UVisionConeComponent : public URealtimeMeshComponent
{
	GENERATED_BODY()

public:	
	UVisionConeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Sets the alert state of the vision cone. */
	void SetAlertState(EAlertState alertState);

	float GetRange() const { return distance; }
	
	float GetAngle() const { return angle; }

private:

	void ConstructSimpleRTMesh();

	void UpdateSimpleRTMesh();
	
	bool GetPoints(TArray<FVector>& outPoints);

	void AppendTriangleMesh(struct FRealtimeMeshSimpleMeshData& MeshData, int32 NewMaterialGroup);
	
	struct FRealtimeMeshSectionConfig OnAddSectionToPolyGroup(int32 PolyGroupIndex);

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	int resolution = 12;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float distance = 200.f;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float angle = 45.f;

	FRealtimeMeshSimpleMeshData meshData;
	
	FRealtimeMeshSectionGroupKey SectionGroupKey;

	UPROPERTY()
	class URealtimeMeshSimple* RealtimeMesh;

	UPROPERTY()
	UMaterialInterface* visionConeMaterialInterface;

	UPROPERTY()
	UMaterialInstanceDynamic* dynamicVisionConeMat;

	UPROPERTY(EditAnywhere, Category="Material Color")
	FVector visionConeColor = FVector(0.f, 0.847059f, 0.094118f); 

	UPROPERTY(EditAnywhere, Category="Material Color")
	FVector visionConeAlertColor = FVector(0.847059f, 0.414904, 0.f); 

	UPROPERTY(EditAnywhere, Category="Material Color")
	FVector visionConeChaseColor = FVector(0.847059f, 0.f, 0.032863f);

		
	TArray<FVector> conePoints;

	FTimerHandle updateMeshTH;
};

enum class EAlertState : uint8 {
	NOTARGET = 0		UMETA(DisplayName="No Target"),
	ALERT = 1			UMETA(DisplayName="Alert"),
	HASTARGET = 2		UMETA(DisplayName="Has Target"),
	MAX	= 3				UMETA(Hidden)
};