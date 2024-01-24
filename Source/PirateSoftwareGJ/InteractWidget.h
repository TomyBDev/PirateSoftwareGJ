// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

class UTextBlock;
class UImage;
class UCanvasPanel;
class USizeBox;
/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//TSharedRef<SWidget> RebuildWidget() override;
	
	//virtual void NativeConstruct() override;

	void NativeOnInitialized() override;

	void IncrementPercentage(float per);

	void ZeroPercentage();

	float GetPercentage() const { return percentage; }

	void SetComplete(bool bComplete);

private:
	UPROPERTY(meta=(BindWidget))
	USizeBox* sizeBox;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* canvas;

	UPROPERTY(meta=(BindWidget))
	UImage* roundProgressImage;

	UPROPERTY(meta=(BindWidget))
	UImage* tickImage;

	UPROPERTY(meta=(BindWidget))
	UImage* backgroundImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* text;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* roundProgressMat;

	UMaterialInstanceDynamic* dynamicRoundProgressMat;

	float percentage = 0;
};
