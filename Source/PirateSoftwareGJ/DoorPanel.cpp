// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "DoorPanel.h"

#include "Door.h"
#include "InteractWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

#define COLLISION_INTERACTION ECC_GameTraceChannel1

// Sets default values
ADoorPanel::ADoorPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	RootComponent = rootComp;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	mesh->SetupAttachment(rootComp);

	interactionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collider"));
	interactionCollider->SetupAttachment(rootComp);
	interactionCollider->SetCollisionResponseToChannel(COLLISION_INTERACTION, ECR_Block);

	interactWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget"));
	interactWidget->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void ADoorPanel::BeginPlay()
{
	Super::BeginPlay();

	interactionWidget = Cast<UInteractWidget>(interactWidget->GetWidget());
	
	interactWidget->SetHiddenInGame(true);
	SetActorTickEnabled(false);
}

// Called every frame
void ADoorPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	percent += DeltaTime;

	if (IsValid(interactionWidget))
		interactionWidget->SetPercentage(percent);
		
}

void ADoorPanel::BeginInteraction_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Begin Interaction!"));
	SetActorTickEnabled(true);
}

void ADoorPanel::EndInteraction_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("End Interaction!"));

	bLockInteraction = true;

	if (IsValid(interactionWidget))
		interactionWidget->SetComplete(true);
	
	if (IsValid(linkedDoor))
		linkedDoor->OpenDoor();

	SetActorTickEnabled(false);
}

void ADoorPanel::InteractionCancelled_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Interaction Cancelled!"));
	percent = 0.f;
	if (IsValid(interactionWidget))
		interactionWidget->SetPercentage(percent);
	SetActorTickEnabled(false);
}

void ADoorPanel::LookatBegin_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Lookat Begin!"));

	if (bLockInteraction)
		return;
	
	percent = 0.f;
	if (IsValid(interactionWidget))
		interactionWidget->SetPercentage(percent);
	interactWidget->SetHiddenInGame(false);
}

void ADoorPanel::LookatEnd_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Lookat End!"));
	interactWidget->SetHiddenInGame(true);
}

