// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMainMenuHUD();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMainMenuWidget* MainMenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> StateWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UGameStateWidget* MainStateWidget;
};
