// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "VisionConeComponent.h"

#include "EnemyAIController.h"
#include "RealtimeMeshComponent.h"
#include "RealtimeMeshSimple.h"
#include "GameFramework/Character.h"
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

	// ...
	
}


// Called when the game starts
void UVisionConeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	// ...
	AEnemyAIController* ai = Cast<AEnemyAIController>(Cast<ACharacter>(GetOwner())->GetController());
	if (IsValid(ai))
	{
		ai->SetPerceptionRange(distance);
		ai->SetPerceptionAngle(angle/2.f);
	}
	
	// Initialize the simple mesh
	RealtimeMesh = InitializeRealtimeMesh<URealtimeMeshSimple>();
	
	// This example create 3 rectangular prisms, one on each axis, with 2 of them grouped in the same vertex buffers, but with different sections
	// This allows for setting up separate materials even if sections share a single set of buffers

	// Setup the two material slots
	RealtimeMesh->SetupMaterialSlot(0, "PrimaryMaterial");

	if (IsValid(visionConeMat))
	{
		SetMaterial(0, visionConeMat);
	}

	{	// Create a basic single section
		

		// This just adds a simple box, you can instead create your own mesh data
		AppendTriangleMesh(meshData, GetPoints(), 1);
		
		// Create a single section, with its own dedicated section group

		SectionGroupKey = FRealtimeMeshSectionGroupKey::Create(0, FName("TestTripleBox"));
		RealtimeMesh->CreateSectionGroup(SectionGroupKey, meshData);

		auto SectionGroup = RealtimeMesh->GetMeshData()->GetSectionGroupAs<FRealtimeMeshSectionGroupSimple>(SectionGroupKey);
		SectionGroup->SetPolyGroupSectionHandler(FRealtimeMeshPolyGroupConfigHandler::CreateUObject(this, &UVisionConeComponent::OnAddSectionToPolyGroup));

		FRealtimeMeshSectionConfig VisibleConfig;
		VisibleConfig.bIsVisible = true;

		RealtimeMesh->UpdateSectionConfig(FRealtimeMeshSectionKey::CreateForPolyGroup(SectionGroupKey, 1), VisibleConfig);
	}
	
}


// Called every frame
void UVisionConeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	TArray<FVector> points = GetPoints();

	for (int i = 0; i < points.Num(); ++i)
	{
		meshData.Positions[i] = points[i];
	}

	RealtimeMesh->UpdateSectionGroup(SectionGroupKey, meshData);
}


TArray<FVector> UVisionConeComponent::GetPoints()
{

	FHitResult hit;

	TArray<FVector> points;

	const FVector startLoc = GetOwner()->GetActorLocation();
	const float angSegment = angle / resolution;
	float ang = -angle / 2.f;

	points.Add({0,0,0});

	for (int i = 0; i < resolution; ++i)
	{
		FVector endLoc = startLoc + (UKismetMathLibrary::RotateAngleAxis(GetOwner()->GetActorForwardVector(), ang,
			GetOwner()->GetActorUpVector()) * distance);

		GetWorld()->LineTraceSingleByChannel(hit, startLoc, endLoc, ECC_Visibility);

		if (hit.bBlockingHit)
		{
			points.Add(UKismetMathLibrary::InverseTransformLocation(GetOwner()->GetActorTransform(),hit.Location));
		}
		else
		{
			points.Add(UKismetMathLibrary::InverseTransformLocation(GetOwner()->GetActorTransform(),endLoc));
		}
		
		ang += angSegment;
	}
	return points;
}

void UVisionConeComponent::AppendTriangleMesh(FRealtimeMeshSimpleMeshData& MeshData, TArray<FVector> Points, int32 NewMaterialGroup)
{
	// Generate verts
	TArray<FVector> BoxVerts;

	for (FVector p : Points)
	{
		BoxVerts.Add(FTransform::Identity.TransformPosition(p));
	}

	const int n = Points.Num() - 2;
	
	// Generate triangles (from quads)
	const int32 StartVertex = MeshData.Positions.Num();
	const int32 NumVerts = Points.Num(); 
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