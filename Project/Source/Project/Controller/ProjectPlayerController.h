// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "ProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AProjectPlayerController();
public:

	UPROPERTY(VisibleAnywhere)
	class AProjectCharacter* MainPlayer;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	/** Block Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* BlockingAction;

	/** Rolling Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RollingAction;

	/** Kick Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* KickAction;


	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	void SetupInputComponent() override;

	/** Called for movement input */
	void RequestMove(const FInputActionValue& Value);
	/** Called for looking input */
	void RequestLook(const FInputActionValue& Value);

	/** Called for jump input **/
	void RequestJumpStart();
	void RequestJumpStop();

	/** Called for attack input **/
	void RequestAttack();

	/** Called for Blocking input **/
	void RequestBlockingStart();
	void RequestBlockingEnd();

	/** Called for Rolling input **/
	void RequestRolling();

	/** Called for Rolling input **/
	void RequestKick();


};
