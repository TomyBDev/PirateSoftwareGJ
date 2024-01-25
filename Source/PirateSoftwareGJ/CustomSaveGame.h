// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "SaveStructs.h"
#include "CustomSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UCustomSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UCustomSaveGame();

	// Save Slot
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString saveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 userIndex;

	// Save Data

	UPROPERTY()
	FPlayerStats playerStats;

	UPROPERTY()
	FGraphicsSettingsStruct graphicsSettings;

	UPROPERTY()
	FGameplaySettingsStruct gameplaySettings;

	UPROPERTY()
	FAudioSettingsStruct audioSettings;

	
	
};
