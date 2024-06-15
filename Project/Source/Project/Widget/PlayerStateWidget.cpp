// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStateWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

#include "Component/CharacterStateComponent.h"
#include "Character/ProjectCharacter.h"


void UPlayerStateWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCanTick();
}

void UPlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetState(InDeltaTime);
}

void UPlayerStateWidget::SetState(float DeltaTime)
{
	if (!Character)
		SetPlayerState();

	if (PlayerStateComponent)
	{
		FCharacterState* CharacterState = &PlayerStateComponent->CharacterState;
		FCharacterState* CurrentState = &PlayerStateComponent->CurrentState;
		float MaxHp = CharacterState->Hp;
		float CurrentHp = CurrentState->Hp;

		HpTextBox->SetText(FText::Format(FTextFormat::FromString("{0} / {1}"), CurrentHp, MaxHp));
		HpBar->SetPercent(CurrentHp / MaxHp);
		CurrentHpIn = UKismetMathLibrary::FInterpTo(CurrentHpIn, CurrentHp, DeltaTime, 3.0f);
		CurrentHpBar->SetPercent(CurrentHpIn / MaxHp);
	}
}

void UPlayerStateWidget::SetPlayerState()
{
	Character = Cast<AProjectCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character)
	{
		PlayerStateComponent = Character->CharacterState;
	}
}