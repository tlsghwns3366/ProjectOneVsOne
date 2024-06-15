// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ProjectMode.h"
#include "Controller/ProjectPlayerController.h"
#include "Character/ProjectCharacter.h"
#include "Widget/PlayerHUD.h"
#include "ProjectStateBase.h"

AProjectMode::AProjectMode()
{
	ConstructorHelpers::FClassFinder<AProjectCharacter>Player(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/Character/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	ConstructorHelpers::FClassFinder<AProjectPlayerController>Controller(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/Controller/BP_PlayerController.BP_PlayerController_C'"));
	if (Player.Succeeded())
	{
		DefaultPawnClass = Player.Class;
	}
	if (Controller.Succeeded())
	{
		PlayerControllerClass = Controller.Class;
	}
	HUDClass = APlayerHUD::StaticClass();
	GameStateClass = AProjectStateBase::StaticClass();
}
