// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "InteractWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"


void UInteractWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	dynamicRoundProgressMat = UMaterialInstanceDynamic::Create(roundProgressMat, this);
	roundProgressImage->SetBrushFromMaterial(dynamicRoundProgressMat);
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("srnetisrntiersatneiartinear starstarstrsw!"));
}

void UInteractWidget::IncrementPercentage(float per)
{
	percentage += per;
	dynamicRoundProgressMat->SetScalarParameterValue("Percentage", percentage);

	if (percentage>=1.f)
		SetComplete(true);
}

void UInteractWidget::ZeroPercentage()
{
	percentage = 0.f;
	dynamicRoundProgressMat->SetScalarParameterValue("Percentage", percentage);
}

void UInteractWidget::SetComplete(bool bComplete)
{
	if (bComplete)
	{
		text->SetVisibility(ESlateVisibility::Hidden);
		tickImage->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	text->SetVisibility(ESlateVisibility::Visible);
	tickImage->SetVisibility(ESlateVisibility::Hidden);
	
	
}
