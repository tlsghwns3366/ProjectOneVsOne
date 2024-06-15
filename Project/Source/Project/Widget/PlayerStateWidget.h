// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AProjectCharacter* Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCharacterStateComponent* PlayerStateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HpTextBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* CurrentHpBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HpBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHpIn;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetState(float DeltaTime);
	void SetPlayerState();
};
