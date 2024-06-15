// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStateComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterState)
	float Hp = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterState)
	float Stamina = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterState)
	float Damage = 10.f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStateComponent();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = CharacterState)
	FCharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterState)
	FCharacterState CurrentState;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool UseHp(float Value);
		
};
