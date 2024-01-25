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

	menuPlayerController = Cast<AMenuPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UCustomGameInstance::SaveGameData(FPlayerStats pStats, FGraphicsSettingsStruct graphics, FGameplaySettingsStruct gameplay, FAudioSettingsStruct audio)
{
	if (UCustomSaveGame* saveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass())))
	{
		// Set up the (optional) delegate.
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		SavedDelegate.BindUObject(this, &UCustomGameInstance::SaveComplete_Delegate);

		// Set data on the savegame object.
		saveGameInstance->playerStats = pStats;
		saveGameInstance->graphicsSettings = graphics;
		saveGameInstance->gameplaySettings = gameplay;
		saveGameInstance->audioSettings = audio;

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(saveGameInstance, FString("MainSaveSlot"), 0, SavedDelegate);
	}
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

	if (IsValid(menuPlayerController))
		menuPlayerController->AddSaveWidget();

	bHasLoaded = true;
}

void UCustomGameInstance::LoadComplete_Delegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UCustomSaveGame* customSaveGame = Cast<UCustomSaveGame>(LoadedGameData);
	if (!IsValid(customSaveGame))
		return;
	
	playerStats = customSaveGame->playerStats;
	graphicsSettings = customSaveGame->graphicsSettings;
	gameplaySettings = customSaveGame->gameplaySettings;
	audioSettings = customSaveGame->audioSettings;

	if (IsValid(menuPlayerController))
		menuPlayerController->RemoveSaveWidget();
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ability 1 level: %i, Ability 2 level: %i, Passive level: %i, "), playerStats.Ability1Level, playerStats.Ability2Level,playerStats.PassiveLevel));
}