// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameStateWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BackgroundBlur.h"
#include "Components/Overlay.h"

void UGameStateWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StateMessage->SetText(FText::FromString("Game Start"));
}

void UGameStateWidget::SetVisible(bool IsBool)
{
	if (IsBool)
	{
		SetVisibility(ESlateVisibility::Visible);
		BackgroundBlur->SetRenderOpacity(1.f);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
		BackgroundBlur->SetRenderOpacity(0.f);
	}
}

void UGameStateWidget::SetUnVisibleDelay()
{
	float VisibilityValue = BackgroundBlur->GetRenderOpacity();
	if (VisibilityValue <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(StateTimerHandle);
		SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(StateTimerHandle, this, &UGameStateWidget::SetUnVisibleDelay, 0.01f, true);
		VisibilityValue = UKismetMathLibrary::FInterpTo(VisibilityValue, VisibilityValue - 1.f, 0.01f, 1.f);
		BackgroundBlur->SetRenderOpacity(VisibilityValue);
	}
}
void UGameStateWidget::SetMessage(FText Value)
{
	StateMessage->SetText(Value);
}

void UGameStateWidget::SetBlurVisible(bool IsBool)
{
	if(IsBool)
		BackgroundBlur->SetRenderOpacity(1.f);
	else
		BackgroundBlur->SetRenderOpacity(0.f);

}

void UGameStateWidget::SetOverlayVisible(bool IsBool)
{
	if (IsBool)
		Overlay->SetRenderOpacity(1.f);
	else
		Overlay->SetRenderOpacity(0.f);
}
