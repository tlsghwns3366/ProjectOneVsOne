// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CharacterStateComponent.h"
#include "DamageActor.h"

// Sets default values for this component's properties
UCharacterStateComponent::UCharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = CharacterState;
	// ...
	
}


// Called every frame
void UCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UCharacterStateComponent::UseHp(float Value)
{
	FVector Location = GetOwner()->GetActorLocation();
	ADamageActor* DamageActor = GetWorld()->SpawnActor<ADamageActor>(DamageActor->StaticClass(), Location, FRotator::ZeroRotator);
	DamageActor->SetDamage(Value);

	CurrentState.Hp = CurrentState.Hp - Value;
	if (CurrentState.Hp <= 0.f)
	{
		CurrentState.Hp = 0.f;
		return false;
	}
	else
	{
		return true;
	}
}
