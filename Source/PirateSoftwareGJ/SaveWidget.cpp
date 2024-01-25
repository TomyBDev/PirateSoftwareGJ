// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "SaveWidget.h"

#include "Components/Border.h"
#include "Components/CircularThrobber.h"
#include "Components/TextBlock.h"

void USaveWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

void USaveWidget::OnComplete()
{
	throbber->SetVisibility(ESlateVisibility::Hidden);
	text->SetText(FText::FromString("Saved Successfully"));
	bg->SetVisibility(ESlateVisibility::Hidden);

	GetWorld()->GetTimerManager().SetTimer(showTH, this, &USaveWidget::HideSelf, showTime, false);
}

void USaveWidget::HideSelf()
{
	SetVisibility(ESlateVisibility::Hidden);
	throbber->SetVisibility(ESlateVisibility::Visible);
	text->SetText(FText::FromString("Saving"));
	bg->SetVisibility(ESlateVisibility::Visible);
}
