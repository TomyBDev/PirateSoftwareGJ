// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "PatrolPointActor.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
APatrolPointActor::APatrolPointActor()
{
	PrimaryActorTick.bCanEverTick = false;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = sceneComp;
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	mesh->SetupAttachment(RootComponent);

	arrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Comp"));
	arrowComp->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void APatrolPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

