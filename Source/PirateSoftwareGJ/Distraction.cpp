// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "Distraction.h"

#include "EnemyCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ADistraction::ADistraction()
{
}

void ADistraction::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;

	if (IsValid(enemyActor))
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), enemyActor, actors);

	for (const auto a : actors)
	{
		enemies.Push(Cast<AEnemyCharacter>(a));
	}
}

void ADistraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADistraction::TurnOff()
{
	distractionAC->SetActive(false);
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, TEXT("SetActive(False)."));

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
		distractionAC = UGameplayStatics::SpawnSound2D(GetWorld(), distractionSound, 1.f,
 1.f, 0.f);

	for (AEnemyCharacter* e : enemies)
	{
		e->InvestigateDistraction(this);
	}
	
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