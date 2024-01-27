// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "MenuGameMode.h"

#include "CustomPlayerController.h"
#include "CustomSaveGame.h"


AMenuGameMode::AMenuGameMode()
{
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();


}

void AMenuGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMenuGameMode::PlayerDied()
{
	ACustomPlayerController* pc = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(pc))
		
	
	GetWorld()->GetTimerManager().SetTimer(deathScreenTH, this, &AMenuGameMode::DeathTimerComplete, deathScreenTime, false);
}

void AMenuGameMode::DeathTimerComplete()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("p_LevelSelectScreen"));
}
