// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AProjectStateBase();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UGameStateWidget* GameStateWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMainMenuWidget* PlayMenuWidget;

	FTimerHandle MenuTimer;
public:
	virtual void BeginPlay() override;
public:
	void PlayerEndText(FText Value);
};
