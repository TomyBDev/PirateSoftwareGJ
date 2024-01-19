// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "DrawDebugHelpers.h"
#include "RealtimeMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RealtimeMeshLibrary.h"
#include "RealtimeMeshSimple.h"
#include "Mesh/RealtimeMeshBasicShapeTools.h"
#include "Mesh/RealtimeMeshBuilder.h"
#include "Mesh/RealtimeMeshSimpleData.h"

static void ConvertToTriangles(TArray<int32>& Triangles, TArray<int32>& MaterialIndices, int32 Vert0, int32 Vert1, int32 Vert2, int32 NewMaterialGroup)
{
	Triangles.Add(Vert0);
	Triangles.Add(Vert1);
	Triangles.Add(Vert2);

	if (NewMaterialGroup != INDEX_NONE)
	{
		MaterialIndices.Add(NewMaterialGroup);
	}
}

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	realtimeMeshComponent = CreateDefaultSubobject<URealtimeMeshComponent>(TEXT("Real Time Mesh Comp"));
	realtimeMeshComponent->SetupAttachment(RootComponent);
	
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize the simple mesh
	URealtimeMeshSimple* RealtimeMesh = realtimeMeshComponent->InitializeRealtimeMesh<URealtimeMeshSimple>();
	
	// This example create 3 rectangular prisms, one on each axis, with 2 of them grouped in the same vertex buffers, but with different sections
	// This allows for setting up separate materials even if sections share a single set of buffers

	// Setup the two material slots
	RealtimeMesh->SetupMaterialSlot(0, "PrimaryMaterial");
	RealtimeMesh->SetupMaterialSlot(1, "SecondaryMaterial");

	{	// Create a basic single section
		FRealtimeMeshSimpleMeshData MeshData;

		// This just adds a simple box, you can instead create your own mesh data
		AppendTriangleMesh(MeshData, GetPoints(), 1);

		// Create a single section, with its own dedicated section group

		const auto SectionGroupKey = FRealtimeMeshSectionGroupKey::Create(0, FName("TestTripleBox"));
		RealtimeMesh->CreateSectionGroup(SectionGroupKey, MeshData);

		auto SectionGroup = RealtimeMesh->GetMeshData()->GetSectionGroupAs<FRealtimeMeshSectionGroupSimple>(SectionGroupKey);
		SectionGroup->SetPolyGroupSectionHandler(FRealtimeMeshPolyGroupConfigHandler::CreateUObject(this, &AEnemyCharacter::OnAddSectionToPolyGroup));

		FRealtimeMeshSectionConfig VisibleConfig;
		VisibleConfig.bIsVisible = true;

		RealtimeMesh->UpdateSectionConfig(FRealtimeMeshSectionKey::CreateForPolyGroup(SectionGroupKey, 1), VisibleConfig);
	}
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
}

TArray<FVector> AEnemyCharacter::GetPoints()
{

	FHitResult hit;

	TArray<FVector> points;

	const FVector startLoc = GetActorLocation();
	const float angSegment = angle / resolution;
	float ang = -angle / 2.f;

	points.Add({0,0,0});

	for (int i = 0; i < resolution; ++i)
	{
		FVector endLoc = startLoc + (UKismetMathLibrary::RotateAngleAxis(GetActorForwardVector(), ang, GetActorUpVector()) * distance);

		GetWorld()->LineTraceSingleByChannel(hit, startLoc, endLoc, ECC_Visibility);

		if (hit.bBlockingHit)
		{
			points.Add(hit.Location - startLoc);
			DrawDebugSphere(GetWorld(), hit.Location, 10.f, 10, FColor::Green, true);
		}
		else
		{
			points.Add(endLoc - startLoc);
			DrawDebugSphere(GetWorld(), endLoc, 10.f, 10, FColor::Red, true);
		}
		
		ang += angSegment;
	}
	return points;
}

FRealtimeMeshSectionConfig AEnemyCharacter::OnAddSectionToPolyGroup(int32 PolyGroupIndex)
{
	return FRealtimeMeshSectionConfig(ERealtimeMeshSectionDrawType::Static, PolyGroupIndex);
}

void AEnemyCharacter::AppendTriangleMesh(FRealtimeMeshSimpleMeshData& MeshData, TArray<FVector> Points, int32 NewMaterialGroup)
{
	// Generate verts
	TArray<FVector> BoxVerts;

	for (FVector p : Points)
	{
		BoxVerts.Add(FTransform::Identity.TransformPosition(p));
	}

	// Generate triangles (from quads)
	const int32 StartVertex = MeshData.Positions.Num();
	const int32 NumVerts = Points.Num(); 
	const int32 NumIndices = (Points.Num()-2) * 3;

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

	const auto WriteToNextThree = [](TArray<FVector>& Array, const FVector& Value)
	{
		Array.Add(Value);
		Array.Add(Value);
		Array.Add(Value);
	};

	const auto WriteTriPositions = [&MeshData](const FVector& VertA, const FVector& VertB, const FVector& VertC)
	{
		MeshData.Positions.Add(VertA);
		MeshData.Positions.Add(VertB);
		MeshData.Positions.Add(VertC);
	};

	for (int i = 0; i < Points.Num()-2; ++i)
	{
		WriteTriPositions(BoxVerts[i+2], BoxVerts[i+1], BoxVerts[0]);
		WriteToNextThree(MeshData.Normals, FTransform::Identity.TransformVectorNoScale(FVector(0.0f, 0.0f, 1.0f)));
		WriteToNextThree(MeshData.Tangents, FTransform::Identity.TransformVectorNoScale(FVector(0.0f, -1.0f, 0.0f)));
		ConvertToTriangles(MeshData.Triangles, MeshData.MaterialIndex, StartVertex + (i*3), StartVertex + (i*3) + 1, StartVertex + (i*3) + 2, NewMaterialGroup);
	}
	
	
	for (int32 Index = 0; Index < Points.Num()-2; Index++)
	{
		MeshData.UV0.Add(FVector2D(0.5f, 0.0f));
		MeshData.UV0.Add(FVector2D(0.0f, 1.0f));
		MeshData.UV0.Add(FVector2D(1.0f, 1.0f));
	}
}

