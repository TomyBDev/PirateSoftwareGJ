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

	bool GetHasLoaded() const { return bHasLoaded; }

	void SetMenuPCRef(AMenuPlayerController* menuPCRef) { menuPlayerController = menuPCRef; }

protected:
	// Called when the game starts or when spawned
	virtual void Init() override;

private:

	UFUNCTION(BlueprintCallable)
	void SaveGameData(FPlayerStats pStats, FGraphicsSettingsStruct graphics, FGameplaySettingsStruct gameplay, FAudioSettingsStruct audio);

	void SaveComplete_Delegate(const FString& slotName, const int32 userIndex, bool bSuccess);

	void LoadGameData();

	void LoadComplete_Delegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);
	
	UPROPERTY()
	FPlayerStats playerStats;

	UPROPERTY()
	FGraphicsSettingsStruct graphicsSettings;

	UPROPERTY()
	FGameplaySettingsStruct gameplaySettings;

	UPROPERTY()
	FAudioSettingsStruct audioSettings;

	UPROPERTY()
	AMenuPlayerController* menuPlayerController;

	bool bHasLoaded = false;

};
