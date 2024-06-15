// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ELevelEnum : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_WeaponEquip UMETA(DisplayName = "WeaponEquip"),
};


UCLASS()
class PROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* OpenLevelButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* OpenLevelBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExitButtonBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

public:

	UFUNCTION()
	void ProjectOpenLevel();
	UFUNCTION()
	void ExitGame();

	void SetGameLevel();
	void SetMainMenuLevel();

};
