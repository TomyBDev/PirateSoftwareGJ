// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "Door.h"

#include "NavLinkComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Comp"));
	RootComponent = collisionBox;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	mesh->SetupAttachment(collisionBox);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OpenDoor()
{
	if (IsValid(closeAnim))
		mesh->PlayAnimation(closeAnim, false);

	collisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	collisionBox->SetCanEverAffectNavigation(false);
	
}

