// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainMenuMode.h"
#include "Widget/MainMenuHUD.h"

AMainMenuMode::AMainMenuMode()
{
	HUDClass = AMainMenuHUD::StaticClass();
	DefaultPawnClass = nullptr;
}
