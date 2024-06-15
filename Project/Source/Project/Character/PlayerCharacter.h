// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ProjectCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API APlayerCharacter : public AProjectCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

public:
	virtual void CharacterDie() override;
	
};
