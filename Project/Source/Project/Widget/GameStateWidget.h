// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UGameStateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StateMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBackgroundBlur* BackgroundBlur;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* Overlay;


	FTimerHandle StateTimerHandle;

public:
	void SetVisible(bool IsBool);
	void SetUnVisibleDelay();
	void SetMessage(FText Value);
	void SetBlurVisible(bool IsBool);
	void SetOverlayVisible(bool IsBool);

};
