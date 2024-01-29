// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

class USaveWidget;
/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	void AddSaveWidget();
	
	void RemoveSaveWidget();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY()
	UUserWidget* menuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> savingWidgetClass;

	UPROPERTY()
	USaveWidget* savingWidget;
};
