// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "CustomGameInstance.h"

#include "CustomSaveGame.h"
#include "MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"

UCustomGameInstance::UCustomGameInstance()
{
}

void UCustomGameInstance::Init()
{
	Super::Init();
	
	// Load Save
	LoadGameData();
}

void UCustomGameInstance::SaveGameData(FGraphicsSettingsStruct graphics, FGeneralSettingsStruct general, FAudioSettingsStruct audio)
{
	if (UCustomSaveGame* saveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass())))
	{
		// Set up the (optional) delegate.
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		SavedDelegate.BindUObject(this, &UCustomGameInstance::SaveComplete_Delegate);

		// Set data on the savegame object.
		saveGameInstance->graphicsSettings = graphics;
		saveGameInstance->generalSettings = general;
		saveGameInstance->audioSettings = audio;

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(saveGameInstance, FString("MainSaveSlot"), 0, SavedDelegate);
		
	}


	graphicsSettings = graphics;
	generalSettings = general;
	audioSettings = audio;

	if (IsValid(menuPlayerController))
		menuPlayerController->AddSaveWidget();
}

void UCustomGameInstance::SaveComplete_Delegate(const FString& slotName, const int32 userIndex, bool bSuccess)
{
	if (IsValid(menuPlayerController))
		menuPlayerController->RemoveSaveWidget();

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save Complete!"));	
}

void UCustomGameInstance::LoadGameData()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	LoadedDelegate.BindUObject(this, &UCustomGameInstance::LoadComplete_Delegate);
	UGameplayStatics::AsyncLoadGameFromSlot(FString("MainSaveSlot"), 0, LoadedDelegate);

	bHasLoaded = true;
}

void UCustomGameInstance::LoadComplete_Delegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UCustomSaveGame* customSaveGame = Cast<UCustomSaveGame>(LoadedGameData);
	if (!IsValid(customSaveGame))
		return;
	
	graphicsSettings = customSaveGame->graphicsSettings;
	generalSettings = customSaveGame->generalSettings;
	audioSettings = customSaveGame->audioSettings;
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ability 1 level: %i, Ability 2 level: %i, Passive level: %i, "), playerStats.Ability1Level, playerStats.Ability2Level,playerStats.PassiveLevel));
}