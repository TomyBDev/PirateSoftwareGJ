// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "VisionConeComponent.h"

#include "DetectionInterface.h"
#include "PlayerCharacter.h"
#include "RealtimeMeshComponent.h"
#include "RealtimeMeshSimple.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

static void ConvertToTriangles(TArray<int32>& Triangles, TArray<int32>& MaterialIndices, int32 Vert0, int32 Vert1, int32 Vert2, int32 NewMaterialGroup)
{
	Triangles.Add(Vert2);
	Triangles.Add(Vert1);
	Triangles.Add(Vert0);

	if (NewMaterialGroup != INDEX_NONE)
	{
		MaterialIndices.Add(NewMaterialGroup);
	}
}

// Sets default values for this component's properties
UVisionConeComponent::UVisionConeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// Get vision cone material interface and store it so we can create dynamic material later.
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> visionConeMaterial(TEXT("/Game/Materials/VisionCone/MatInst_VisionCone.MatInst_VisionCone"));
	if (visionConeMaterial.Succeeded())
		visionConeMaterialInterface = visionConeMaterial.Object;
}

// Called when the game starts
void UVisionConeComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Player Reference
	playerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Create dynamic material for vision cone.
	dynamicVisionConeMat = UMaterialInstanceDynamic::Create(visionConeMaterialInterface, this);
	
	// Construct initial simple realtime mesh.
	ConstructSimpleRTMesh();

	// Update Mesh Every Interval
	GetWorld()->GetTimerManager().SetTimer(updateMeshTH, this, &UVisionConeComponent::UpdateSimpleRTMesh, 0.16f, true);

	// Update Mesh Every Interval
	GetWorld()->GetTimerManager().SetTimer(playerDetectionUpdateTH, this, &UVisionConeComponent::PlayerDetection, 0.16f, true);
}

// Called every frame
void UVisionConeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UVisionConeComponent::SetAlertState(EAlertState alertState)
{
	// Dynamic material is ded.
	if (!IsValid(dynamicVisionConeMat))
		return;

	// Update the color of the dynamic material instance, to match the state.
	switch (alertState) {
		
		case EAlertState::NOTARGET:
			dynamicVisionConeMat->SetVectorParameterValue(TEXT("Color"), visionConeColor);
			break;
			
		case EAlertState::ALERT:
			dynamicVisionConeMat->SetVectorParameterValue(TEXT("Color"), visionConeAlertColor);
			break;
		
		case EAlertState::HASTARGET:
			dynamicVisionConeMat->SetVectorParameterValue(TEXT("Color"), visionConeChaseColor);
			break;

		default:
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, TEXT("Invalid Alert State."));
	}
}

void UVisionConeComponent::SetDisabled(bool bDis)
{
	SetHiddenInGame(bDis);
	bDisabled = bDis;
}

void UVisionConeComponent::ConstructSimpleRTMesh()
{
	// Initialize the simple mesh
	RealtimeMesh = InitializeRealtimeMesh<URealtimeMeshSimple>();

	// Setup the material slot for the vision cone.
	RealtimeMesh->SetupMaterialSlot(0, "PrimaryMaterial");

	// Bind the dynamic material we created.
	if (IsValid(dynamicVisionConeMat))
	{
		SetMaterial(0, dynamicVisionConeMat);
	}

	{	// Create a basic single section
		
		// Generate initial cone points.
		for (int i = 0; i < resolution+1; ++i)
			conePoints.Add(FVector(0,0,0));	
		
		GetPoints(conePoints);

		// Generate and store the vision cones triangle mesh data.
		AppendTriangleMesh(meshData, 1);
		
		// Creates a group for the mesh data (Not sure if needed as we only have one group, but it works i guess).
		SectionGroupKey = FRealtimeMeshSectionGroupKey::Create(0, FName("VisionCone"));
		RealtimeMesh->CreateSectionGroup(SectionGroupKey, meshData);

		auto SectionGroup = RealtimeMesh->GetMeshData()->GetSectionGroupAs<FRealtimeMeshSectionGroupSimple>(SectionGroupKey);
		SectionGroup->SetPolyGroupSectionHandler(FRealtimeMeshPolyGroupConfigHandler::CreateUObject(this, &UVisionConeComponent::OnAddSectionToPolyGroup));

		// Create config for mesh.
		FRealtimeMeshSectionConfig VisibleConfig;
		VisibleConfig.bIsVisible = true;

		// Update the mesh with the mesh data we created.
		RealtimeMesh->UpdateSectionConfig(FRealtimeMeshSectionKey::CreateForPolyGroup(SectionGroupKey, 1), VisibleConfig);
	}
}

void UVisionConeComponent::UpdateSimpleRTMesh()
{
	if (bDisabled)
		return;
	
	// Send out ray casts to get the vision cone shape outline points.
	if (GetPoints(conePoints))
	{
		// For each outline point, update the vertex point in the mesh data.
		for (int i = 0; i < conePoints.Num(); ++i)
			meshData.Positions[i] = conePoints[i];

		// Update 
		RealtimeMesh->UpdateSectionGroup(SectionGroupKey, meshData);
	}
}

bool UVisionConeComponent::GetPoints(TArray<FVector>& outPoints)
{
	bool bShouldUpdate = false;
	
	FHitResult hit;

	const FVector startLoc = GetComponentLocation();
	const float angSegment = angle / resolution;
	float ang = -angle / 2.f;

	for (int i = 0; i < resolution; ++i)
	{
		FVector endLoc = startLoc + (UKismetMathLibrary::RotateAngleAxis(GetForwardVector(), ang,
			FVector(0,0,1)) * maxRange);

		GetWorld()->LineTraceSingleByChannel(hit, startLoc, endLoc, ECC_Visibility);

		FVector point;
		
		if (hit.bBlockingHit)
			point = UKismetMathLibrary::InverseTransformLocation(GetComponentTransform(),hit.Location);
		else
		
			point = UKismetMathLibrary::InverseTransformLocation(GetComponentTransform(),endLoc);
		
		
		if (point != outPoints[i+1])
		{
			outPoints[i+1] = point;
			bShouldUpdate = true;
		}
		
		ang += angSegment;
	}
	return bShouldUpdate;
}

void UVisionConeComponent::AppendTriangleMesh(FRealtimeMeshSimpleMeshData& MeshData, int32 NewMaterialGroup)
{
	// Generate verts
	TArray<FVector> BoxVerts;

	for (FVector p : conePoints)
	{
		BoxVerts.Add(FTransform::Identity.TransformPosition(p));
	}

	const int n = conePoints.Num() - 2;
	
	// Generate triangles (from quads)
	const int32 StartVertex = MeshData.Positions.Num();
	const int32 NumVerts = conePoints.Num(); 
	const int32 NumIndices = n * 3;

	// Make sure the secondary arrays are the same length, zeroing them if necessary
	MeshData.Normals.SetNumZeroed(StartVertex);
	MeshData.Tangents.SetNumZeroed(StartVertex);
	MeshData.UV0.SetNumZeroed(StartVertex);

	MeshData.Positions.Reserve(StartVertex + NumVerts);
	MeshData.Normals.Reserve(StartVertex + NumVerts);
	MeshData.Tangents.Reserve(StartVertex + NumVerts);
	MeshData.UV0.Reserve(StartVertex + NumVerts);
	MeshData.Triangles.Reserve(MeshData.Triangles.Num() + NumIndices);

	if (NewMaterialGroup != INDEX_NONE)
	{
		const int32 NumExistingTriangles = (MeshData.Triangles.Num()) / 3;
		const int32 NumTrianglesToAdd = NumIndices / 3;
		MeshData.MaterialIndex.Reserve(NumExistingTriangles + NumTrianglesToAdd);
		MeshData.MaterialIndex.SetNumZeroed(NumExistingTriangles);
	}

	MeshData.Positions.Add(BoxVerts[0]);
	MeshData.Normals.Add(FTransform::Identity.TransformVectorNoScale(FVector(0.0f, 0.0f, 1.0f)));
	MeshData.Tangents.Add(FTransform::Identity.TransformVectorNoScale(FVector(0.0f, -1.0f, 0.0f)));
	
	MeshData.Positions.Add(BoxVerts[1]);
	MeshData.Normals.Add(FTransform::Identity.TransformVectorNoScale(FVector(0.0f, 0.0f, 1.0f)));
	MeshData.Tangents.Add(FTransform::Identity.TransformVectorNoScale(FVector(0.0f, -1.0f, 0.0f)));

	for (int i = 0; i < n; ++i)
	{
		MeshData.Positions.Add(BoxVerts[i+2]);
		MeshData.Normals.Add(FTransform::Identity.TransformVectorNoScale(FVector(0.0f, 0.0f, 1.0f)));
		MeshData.Tangents.Add(FTransform::Identity.TransformVectorNoScale(FVector(0.0f, -1.0f, 0.0f)));
		ConvertToTriangles(MeshData.Triangles, MeshData.MaterialIndex, StartVertex , StartVertex + i + 1, StartVertex + i + 2, NewMaterialGroup);
		MeshData.UV0.Add(FVector2D((i+1)/static_cast<float>(n), 0.0f)); //2
		MeshData.UV0.Add(FVector2D(i/static_cast<float>(n), 0.0f)); //1
		MeshData.UV0.Add(FVector2D(0.5f, 1.0f)); //0
	}
}

FRealtimeMeshSectionConfig UVisionConeComponent::OnAddSectionToPolyGroup(int32 PolyGroupIndex)
{
	return FRealtimeMeshSectionConfig(ERealtimeMeshSectionDrawType::Static, PolyGroupIndex);
}

void UVisionConeComponent::PlayerDetection()
{
	if (!IsValid(playerRef) || bDisabled)
		return;

	// Do visibility check on player. Otherwise player will be spotted through wall.
	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(hit, GetComponentLocation(), playerRef->GetActorLocation(), ECC_Visibility);
	if (hit.GetActor() != playerRef)
		return;
	

	// Get the distance to the player.
	const float distance = FVector::Dist(playerRef->GetActorLocation(), GetComponentLocation());

	// If the player is not cloaked or in the max range.
	if (!playerRef->GetIsCloaked() && distance < maxRange)
	{
		const float componentDP = GetForwardVector().Dot(UKismetMathLibrary::GetDirectionUnitVector(GetComponentLocation(),playerRef->GetActorLocation()));

		// If the player is in peripheral range or is in the angle specified for the max range.
		if (distance < peripheralRange || acos(componentDP) < FMath::DegreesToRadians(angle/2.f))
		{
			SetAlertState(EAlertState::HASTARGET);
			
			AActor* owner = GetOwner();
			if (UKismetSystemLibrary::DoesImplementInterface(owner, UDetectionInterface::StaticClass())) {				
				IDetectionInterface::Execute_StartDetection(owner, playerRef);
			}

			bPlayerInRange = true;
			return;
		}
	}

	// If player was previously in range and has left the come inform owner.
	if (bPlayerInRange)
	{
		SetAlertState(EAlertState::ALERT);

		GetWorld()->GetTimerManager().SetTimer(playerLostTH, this, &UVisionConeComponent::PlayerLost, losePlayerTime);
		
		AActor* owner = GetOwner();
		if (UKismetSystemLibrary::DoesImplementInterface(owner, UDetectionInterface::StaticClass())) {				
			IDetectionInterface::Execute_EndDetection(owner, playerRef);
		}

		bPlayerInRange = false;
	}
	
}

void UVisionConeComponent::PlayerLost()
{
	SetAlertState(EAlertState::NOTARGET);
}
