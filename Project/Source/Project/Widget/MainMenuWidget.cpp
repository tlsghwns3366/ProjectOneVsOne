// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextBlock.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (GetWorld())
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	}

	OpenLevelButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ProjectOpenLevel);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
	SetGameLevel();
}

void UMainMenuWidget::ProjectOpenLevel()
{
	if (GetWorld())
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UMainMenuWidget::ExitGame()
{
	if (GetWorld())
		UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Type::Quit, false);
}

void UMainMenuWidget::SetGameLevel()
{
	LevelName = "GameStart";
	OpenLevelBox->SetText(FText::FromString("Game Start"));
}

void UMainMenuWidget::SetMainMenuLevel()
{
	LevelName = "MainMenu";
	OpenLevelBox->SetText(FText::FromString("Main Menu"));
}