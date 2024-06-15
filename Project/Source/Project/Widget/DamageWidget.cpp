// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageWidget.h"
#include "DamageWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

void UDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamageWidget::SetDamageText(FText Name)
{
	DamageTextBox->SetText(Name);

	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(DamageTextBox->Slot);
	float X = FMath::FRandRange(-50.f, 50.f);
	float Y = FMath::FRandRange(-20.f, 20.f);
	if (PanelSlot)
	{
		PanelSlot->SetPosition(FVector2D(X, Y));
	}
}
