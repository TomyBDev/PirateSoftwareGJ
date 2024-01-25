// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "MenuPlayerController.h"

#include "CustomGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (!IsValid(MenuWidgetClass))
		return;

	menuWidget = CreateWidget(this, MenuWidgetClass);
	
	if (IsValid(menuWidget))
		menuWidget->AddToViewport();

	UCustomGameInstance* cgi = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(cgi) && !cgi->GetHasLoaded())
		AddSaveWidget();
}

void AMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMenuPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMenuPlayerController::AddSaveWidget()
{

	if (IsValid(savingWidget))
	{
		savingWidget->AddToViewport();
		return;
	}
	
	if (!IsValid(savingWidgetClass))
		return;

	savingWidget = CreateWidget(this, savingWidgetClass);
	
	if (IsValid(savingWidget))
		savingWidget->AddToViewport();
	
}

void AMenuPlayerController::RemoveSaveWidget()
{
	if (!IsValid(savingWidget))
		return;

	savingWidget->RemoveFromParent();
}
