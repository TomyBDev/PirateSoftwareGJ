// Copyright Epic Games, Inc. All Rights Reserved.


#include "MainGameModeBase.h"

#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMainGameModeBase::AMainGameModeBase()
{
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainGameModeBase::PlayerDied()
{
	ACustomPlayerController* pc = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(pc))
		pc->SetPlayerDied();
		
		GetWorld()->GetTimerManager().SetTimer(deathScreenTH, this, &AMainGameModeBase::DeathTimerComplete, deathScreenTime, false);
}

void AMainGameModeBase::PlayerWon()
{
	ACustomPlayerController* pc = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(pc))
		pc->SetPlayerWon();
		
	GetWorld()->GetTimerManager().SetTimer(deathScreenTH, this, &AMainGameModeBase::DeathTimerComplete, deathScreenTime, false);
}

void AMainGameModeBase::DeathTimerComplete()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("p_LevelSelectScreen"));
}
