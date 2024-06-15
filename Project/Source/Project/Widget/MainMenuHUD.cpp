// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainMenuHUD.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BackgroundBlur.h"

#include "MainMenuWidget.h"
#include "Widget/GameStateWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>StateBlueprintWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_StateWidget.WBP_StateWidget_C'"));
	if (StateBlueprintWidget.Succeeded())
	{
		StateWidget = StateBlueprintWidget.Class;
	}
	MainStateWidget = CreateWidget<UGameStateWidget>(GetWorld(), StateWidget);
	if (MainStateWidget)
	{
		MainStateWidget->AddToViewport();
		MainStateWidget->SetMessage(FText::FromString("1 vs 1"));
		MainStateWidget->SetBlurVisible(false);
		MainStateWidget->SetOverlayVisible(true);
	}
	static ConstructorHelpers::FClassFinder<UUserWidget>MenuBlueprintWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_MainMenu.WBP_MainMenu_C'"));
	if (MenuBlueprintWidget.Succeeded())
	{
		Widget = MenuBlueprintWidget.Class;
	}
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), Widget);
	if(MainMenuWidget)
		MainMenuWidget->AddToViewport();
}