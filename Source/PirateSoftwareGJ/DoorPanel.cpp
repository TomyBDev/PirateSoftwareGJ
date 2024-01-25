// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "DoorPanel.h"

#include "Door.h"
#include "InteractWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADoorPanel::ADoorPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoorPanel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
}

bool ADoorPanel::BeginInteraction_Implementation()
{
	if (Super::BeginInteraction_Implementation())
		return true;

	return false;
}

bool ADoorPanel::EndInteraction_Implementation()
{
	if (Super::EndInteraction_Implementation())
		return true;
	
	if (IsValid(linkedDoor))
		linkedDoor->OpenDoor();

	return false;
}

bool ADoorPanel::InteractionCancelled_Implementation()
{
	if (Super::InteractionCancelled_Implementation())
		return true;

	return false;
}

bool ADoorPanel::LookatBegin_Implementation()
{
	if (Super::LookatBegin_Implementation())
		return true;

	return false;
}

bool ADoorPanel::LookatEnd_Implementation()
{
	if (Super::LookatEnd_Implementation())
		return true;

	return false;
}

