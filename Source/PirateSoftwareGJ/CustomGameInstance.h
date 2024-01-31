// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveStructs.h"
#include "CustomGameInstance.generated.h"

class AMenuPlayerController;
class USaveGame;
/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCustomGameInstance();

	/** Getters. */

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FGraphicsSettingsStruct GetGraphicsSettings() const { return graphicsSettings; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FGeneralSettingsStruct GetGeneralSettings() const { return generalSettings; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FAudioSettingsStruct GetAudioSettings() const { return audioSettings; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	uint8 GetCompletedLevels() const { return completeLevels; }

	uint8 GetCurrentLevel() const { return currentLevel; }
	
	bool GetHasLoaded() const { return bHasLoaded; }

	/** Setters. */

	UFUNCTION(BlueprintSetter, BlueprintInternalUseOnly)
	void SetCurrentLevel(uint8 level) {currentLevel = level; }
	
	void SetMenuPCRef(AMenuPlayerController* menuPCRef) { menuPlayerController = menuPCRef; }
	
	void SetCompletedLevels(uint8 levels) { completeLevels = levels; }

protected:
	// Called when the game starts or when spawned
	virtual void Init() override;

private:

	/** Saving. */

	UFUNCTION(BlueprintCallable)
	void SaveGameData(FGraphicsSettingsStruct graphics, FGeneralSettingsStruct general, FAudioSettingsStruct audio);

	void SaveComplete_Delegate(const FString& slotName, const int32 userIndex, bool bSuccess);

	/** Loading. */
	
	void LoadGameData();

	void LoadComplete_Delegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);
	
	UPROPERTY()
	FPlayerStats playerStats;

	UPROPERTY(BlueprintGetter=GetGraphicsSettings)
	FGraphicsSettingsStruct graphicsSettings;

	UPROPERTY(BlueprintGetter = GetGeneralSettings)
	FGeneralSettingsStruct generalSettings;

	UPROPERTY(BlueprintGetter = GetAudioSettings)
	FAudioSettingsStruct audioSettings;

	UPROPERTY()
	AMenuPlayerController* menuPlayerController;

	UPROPERTY(BlueprintGetter=GetCompletedLevels)
	uint8 completeLevels = 0;

	UPROPERTY(BlueprintSetter=SetCurrentLevel)
	uint8 currentLevel = 1;
	
	bool bHasLoaded = false;

};
