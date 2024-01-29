// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "MenuPlayerController.h"

#include "CustomGameInstance.h"
#include "SaveWidget.h"
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
	if (IsValid(cgi))
	{
		cgi->SetMenuPCRef(this);
		
		AddSaveWidget();

		if (cgi->GetHasLoaded())
		{
			if (IsValid(savingWidget))
				savingWidget->OnComplete();
		}
	}
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
		savingWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	if (!IsValid(savingWidgetClass))
		return;

	savingWidget = Cast<USaveWidget>(CreateWidget(this, savingWidgetClass));
	
	if (IsValid(savingWidget))
		savingWidget->AddToViewport(100);
	
}

void AMenuPlayerController::RemoveSaveWidget()
{
	if (!IsValid(savingWidget))
		return;

	savingWidget->OnComplete();
}
