// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerHUD.h"
#include "Components/WidgetComponent.h"
APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>BlueprintWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_PlayerState.WBP_PlayerState_C'"));
	if (BlueprintWidget.Succeeded())
	{
		Widget = BlueprintWidget.Class;
	}
	PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
	if (PlayerWidget)
		PlayerWidget->AddToViewport();
}