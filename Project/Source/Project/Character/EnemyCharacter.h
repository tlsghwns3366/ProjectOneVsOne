// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ProjectCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AEnemyCharacter : public AProjectCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* EnemyStateWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UWidgetComponent* WidgetComponent;

public:
	virtual void BeginPlay() override;
public:
	virtual void Attack() override;
	virtual void CharacterDie() override;
	virtual void SetStun() override;

	void SetTarget(AActor* Actor);
	void SetStunTimer();
};
