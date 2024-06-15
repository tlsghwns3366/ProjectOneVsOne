// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DamageType_Physical.h"
#include "CharacterStateComponent.h"

bool UDamageType_Physical::SetAttackType(UCharacterStateComponent* CharacterStateComponent, float Damage) const
{
	return CharacterStateComponent->UseHp(Damage);
}
