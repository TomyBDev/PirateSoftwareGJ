// Copyright Epic Games, Inc. All Rights Reserved.


#include "MainGameModeBase.h"

#include "CustomGameInstance.h"
#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMainGameModeBase::AMainGameModeBase()
{
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	customGameInstance = Cast<UCustomGameInstance>(GetGameInstance());
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
	// Let Player Controller know the player won so it can display the win screen.
	ACustomPlayerController* pc = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(pc))
		pc->SetPlayerWon();

	// If this is the latest level, mark it as complete.
	if (IsValid(customGameInstance) && customGameInstance->GetCurrentLevel() > customGameInstance->GetCompletedLevels())
		customGameInstance->SetCompletedLevels(customGameInstance->GetCurrentLevel());
	
	// Start the death timer so we can move back to level select after it.
	GetWorld()->GetTimerManager().SetTimer(deathScreenTH, this, &AMainGameModeBase::DeathTimerComplete, deathScreenTime, false);
}

void AMainGameModeBase::DeathTimerComplete()
{
	if (!IsValid(customGameInstance))
		return;

	switch (customGameInstance->GetCompletedLevels())
	{
	case 1:
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("p_LevelSelect1"));
		return;

	case 2:
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("p_LevelSelect2"));
		return;

	case 3:
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("p_LevelSelect3"));
		return;
		
	default:
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("p_LevelSelectScreen"));
	}
		
}
