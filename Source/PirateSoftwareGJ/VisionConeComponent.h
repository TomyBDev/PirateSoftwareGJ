// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "RealtimeMeshComponent.h"
#include "Mesh/RealtimeMeshSimpleData.h"
#include "VisionConeComponent.generated.h"


class APlayerCharacter;
struct FRealtimeMeshSimpleMeshData;
struct FRealtimeMeshSectionConfig;
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

	float GetRange() const { return maxRange; }
	
	float GetAngle() const { return angle; }

private:

	/** Vision Cone Settings */

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	int resolution = 20;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float maxRange = 500.f;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float peripheralRange = 100.f;

	UPROPERTY(EditAnywhere, Category="Vision Cone")
	float angle = 45.f;
	

	/** Realtime Mesh. */

	void ConstructSimpleRTMesh();

	void UpdateSimpleRTMesh();
	
	bool GetPoints(TArray<FVector>& outPoints);

	void AppendTriangleMesh(FRealtimeMeshSimpleMeshData& MeshData, int32 NewMaterialGroup);
	
	FRealtimeMeshSectionConfig OnAddSectionToPolyGroup(int32 PolyGroupIndex);

	FRealtimeMeshSimpleMeshData meshData;
	
	FRealtimeMeshSectionGroupKey SectionGroupKey;

	UPROPERTY()
	class URealtimeMeshSimple* RealtimeMesh;

	TArray<FVector> conePoints;

	FTimerHandle updateMeshTH;

	
	/** Vision Cone Material */

	UPROPERTY(EditAnywhere, Category="Material Color")
	FVector visionConeColor = FVector(0.f, 0.847059f, 0.094118f); 

	UPROPERTY(EditAnywhere, Category="Material Color")
	FVector visionConeAlertColor = FVector(0.847059f, 0.414904, 0.f); 

	UPROPERTY(EditAnywhere, Category="Material Color")
	FVector visionConeChaseColor = FVector(0.847059f, 0.f, 0.032863f);

	UPROPERTY()
	UMaterialInterface* visionConeMaterialInterface;

	UPROPERTY()
	UMaterialInstanceDynamic* dynamicVisionConeMat;

	
	/** Player Detection. */

	void PlayerDetection();

	bool bPlayerInRange = false;
	 
	FTimerHandle playerDetectionUpdateTH;

	void PlayerLost();
	
	FTimerHandle playerLostTH;

	UPROPERTY(EditAnywhere)
	float losePlayerTime = 5.f;

	
	/** Misc. */

	APlayerCharacter* playerRef;
};

enum class EAlertState : uint8 {
	NOTARGET = 0		UMETA(DisplayName="No Target"),
	ALERT = 1			UMETA(DisplayName="Alert"),
	HASTARGET = 2		UMETA(DisplayName="Has Target"),
	MAX	= 3				UMETA(Hidden)
};