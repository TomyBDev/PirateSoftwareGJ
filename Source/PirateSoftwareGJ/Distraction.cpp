// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "Distraction.h"

#include "Kismet/GameplayStatics.h"

ADistraction::ADistraction()
{
}

void ADistraction::BeginPlay()
{
	Super::BeginPlay();
}

void ADistraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADistraction::BeginInteraction_Implementation()
{
	if (Super::BeginInteraction_Implementation())
		return true;

	return false;
}

bool ADistraction::EndInteraction_Implementation()
{
	if (Super::EndInteraction_Implementation())
		return true;

	if (IsValid(distractionSound))
		UGameplayStatics::PlaySound2D(GetWorld(), distractionSound, 1.f,
 1.f, 0.f);
	
	return false;
}

bool ADistraction::InteractionCancelled_Implementation()
{
	if (Super::InteractionCancelled_Implementation())
		return true;

	return false;
	
}

bool ADistraction::LookatBegin_Implementation()
{
	if (Super::LookatBegin_Implementation())
		return true;

	return false;
	
}

bool ADistraction::LookatEnd_Implementation()
{
	if (Super::LookatEnd_Implementation())
		return true;

	return false;
	
}