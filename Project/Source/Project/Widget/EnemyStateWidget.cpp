// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnemyStateWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

#include "Component/CharacterStateComponent.h"
#include "Character/ProjectCharacter.h"

void UEnemyStateWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCanTick();
}

void UEnemyStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetState(InDeltaTime);
}

void UEnemyStateWidget::SetState(float DeltaTime)
{
	if (CharacterStateComponent)
	{
		FCharacterState* CharacterState = &CharacterStateComponent->CharacterState;
		FCharacterState* CurrentState = &CharacterStateComponent->CurrentState;
		float MaxHp = CharacterState->Hp;
		float CurrentHp = CurrentState->Hp;

		HpBar->SetPercent(CurrentHp / MaxHp);
		CurrentHpIn = UKismetMathLibrary::FInterpTo(CurrentHpIn, CurrentHp, DeltaTime, 3.0f);
		CurrentHpBar->SetPercent(CurrentHpIn / MaxHp);
	}
}

void UEnemyStateWidget::SetCharacter(AProjectCharacter* Value)
{
	if (Value)
	{
		Character = Value;
		CharacterStateComponent = Character->CharacterState;
	}
}
