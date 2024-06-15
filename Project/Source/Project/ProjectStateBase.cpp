// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectStateBase.h"
#include "Components/WidgetComponent.h"
#include "Widget/GameStateWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Widget/MainMenuWidget.h"

AProjectStateBase::AProjectStateBase()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>BlueprintWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_StateWidget.WBP_StateWidget_C'"));
	if (BlueprintWidget.Succeeded())
	{
		Widget = BlueprintWidget.Class;
	}
	GameStateWidget = CreateWidget<UGameStateWidget>(GetWorld(), Widget);
	static ConstructorHelpers::FClassFinder<UUserWidget>BlueprintMenuWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_MainMenu.WBP_MainMenu_C'"));
	if (BlueprintMenuWidget.Succeeded())
	{
		MenuWidget = BlueprintMenuWidget.Class;
	}
	PlayMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MenuWidget);
}

void AProjectStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (GameStateWidget)
	{
		GameStateWidget->AddToViewport();
		GameStateWidget->SetVisible(true);
		GameStateWidget->SetOverlayVisible(true);
		GameStateWidget->SetUnVisibleDelay();
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
}

void AProjectStateBase::PlayerEndText(FText Value)
{
	GameStateWidget->SetVisible(true);
	GameStateWidget->SetMessage(Value);
	GameStateWidget->SetOverlayVisible(false);
	if (PlayMenuWidget)
	{
		GetWorld()->GetTimerManager().SetTimer(MenuTimer, [&]() {
			PlayMenuWidget->AddToViewport();
			PlayMenuWidget->SetMainMenuLevel();
			}, 2.f, false);
	}
}
