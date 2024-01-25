// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API USaveWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void NativeOnInitialized() override;

	void OnComplete();

	void HideSelf();

private:

	UPROPERTY(meta=(BindWidget))
	class UCircularThrobber* throbber;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text;

	UPROPERTY(meta=(BindWidget))
	class UBorder* bg;


	FTimerHandle showTH;

	float showTime = 4.f;
};
