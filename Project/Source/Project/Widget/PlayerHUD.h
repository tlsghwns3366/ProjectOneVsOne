// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	APlayerHUD();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* PlayerWidget;
	
};
