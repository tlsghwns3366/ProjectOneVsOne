// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ProjectPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Character/ProjectCharacter.h"
#include "ProjectAnimInstance.h"

AProjectPlayerController::AProjectPlayerController()
{
}

void AProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainPlayer = Cast<AProjectCharacter>(GetCharacter());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AProjectPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// ** Moving ** //
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestMove);

		// ** Looking ** //
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestLook);
		//** Jumping **//
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AProjectPlayerController::RequestJumpStop);

		// ** ATTACK ** //
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestAttack);

		// ** BLOCKING ** //
		EnhancedInputComponent->BindAction(BlockingAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestBlockingStart);
		EnhancedInputComponent->BindAction(BlockingAction, ETriggerEvent::Completed, this, &AProjectPlayerController::RequestBlockingEnd);


		// ** ROLLING ** //
		EnhancedInputComponent->BindAction(RollingAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestRolling);

		// ** Kick ** //
		EnhancedInputComponent->BindAction(KickAction, ETriggerEvent::Triggered, this, &AProjectPlayerController::RequestKick);

	}
}

void AProjectPlayerController::RequestMove(const FInputActionValue& Value)
{
	if (MainPlayer)
	{
		if (MainPlayer->Anim->IsStun)
			return;
		FVector2D MovementVector = Value.Get<FVector2D>();
		// find out which way is forward
		const FRotator Rotation = MainPlayer->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		if (MainPlayer->Anim)
		{
			MainPlayer->Anim->ForwardInput = MovementVector.Y;
			MainPlayer->Anim->SideInput = MovementVector.X;
		}
		MainPlayer->AddMovementInput(ForwardDirection, MovementVector.Y);
		MainPlayer->AddMovementInput(RightDirection, MovementVector.X);
	}
}
void AProjectPlayerController::RequestLook(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (MainPlayer)
	{
		// add yaw and pitch input to controller
		MainPlayer->AddControllerYawInput(-LookAxisVector.X);
		MainPlayer->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectPlayerController::RequestJumpStart()
{
	MainPlayer->JumpStart();
}

void AProjectPlayerController::RequestJumpStop()
{
	MainPlayer->JumpEnd();
}

void AProjectPlayerController::RequestAttack()
{
	MainPlayer->Attack();
}
void AProjectPlayerController::RequestBlockingStart()
{
	MainPlayer->SetBlocking(true);
}

void AProjectPlayerController::RequestBlockingEnd()
{
	MainPlayer->SetBlocking(false);
}

void AProjectPlayerController::RequestRolling()
{
	MainPlayer->Rolling();
}

void AProjectPlayerController::RequestKick()
{
	MainPlayer->KickAttack();
}
