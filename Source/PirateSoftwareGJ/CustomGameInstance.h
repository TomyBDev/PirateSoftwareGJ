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

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FGraphicsSettingsStruct GetGraphicsSettings() const { return graphicsSettings; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FGeneralSettingsStruct GetGeneralSettings() const { return generalSettings; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FAudioSettingsStruct GetAudioSettings() const { return audioSettings; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool IsLevel1Complete() const { return bLevel1Complete; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool IsLevel2Complete() const { return bLevel2Complete; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool IsLevel3Complete() const { return bLevel3Complete; }

	bool GetHasLoaded() const { return bHasLoaded; }

	void SetMenuPCRef(AMenuPlayerController* menuPCRef) { menuPlayerController = menuPCRef; }

protected:
	// Called when the game starts or when spawned
	virtual void Init() override;

private:

	UFUNCTION(BlueprintCallable)
	void SaveGameData(FGraphicsSettingsStruct graphics, FGeneralSettingsStruct general, FAudioSettingsStruct audio);

	void SaveComplete_Delegate(const FString& slotName, const int32 userIndex, bool bSuccess);

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

	UPROPERTY(BlueprintGetter=IsLevel1Complete)
	bool bLevel1Complete = false;

	UPROPERTY(BlueprintGetter=IsLevel2Complete)
	bool bLevel2Complete = false;

	UPROPERTY(BlueprintGetter=IsLevel3Complete)
	bool bLevel3Complete = false;

	UPROPERTY()
	AMenuPlayerController* menuPlayerController;

	bool bHasLoaded = false;

};
