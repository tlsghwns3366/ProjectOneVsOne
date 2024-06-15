// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Character/ProjectCharacter.h"

void UProjectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Character = Cast<AProjectCharacter>(Pawn);
		if (IsValid(Character))
		{
			CharacterMovement = Character->GetCharacterMovement();
			SkeletalMeshComponent = Character->GetMesh();
		}
	}
}

void UProjectAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UProjectAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character)
	{
		Velocity = CharacterMovement->Velocity;
		Speed = Velocity.Length();
		IsMoving = Speed > 3.0f;
		IsFalling = CharacterMovement->IsFalling();
		DeltaTimeX = DeltaSeconds;
		SetCharacterState();
		if (IsFalling)
			IsBlocking = false;
		if(IsBlocking)
			SetBlockRotation();
	}
}

void UProjectAnimInstance::SetCharacterState()
{
	if (Character)
	{
		if (Character->CharacterWeapon)
			CharacterState = ECharacterState::E_WeaponEquip;
		else
			CharacterState = ECharacterState::E_Idle;
	}
}

void UProjectAnimInstance::AnimNotify_StartTrace()
{
	AttackStartTrace.Broadcast();
}

void UProjectAnimInstance::AnimNotify_KickStart()
{
	AttackKickTrace.Broadcast();
}

void UProjectAnimInstance::SetBlockRotation()
{
	if (Character)
	{
		FRotator CharacterRotator = Character->GetActorRotation();
		FRotator ControllerRotator = Character->GetController()->GetControlRotation();
		float InYaw = UKismetMathLibrary::RInterpTo(CharacterRotator, ControllerRotator, DeltaTimeX, 30.f).Yaw;
		Character->SetActorRotation(FRotator(0.f, InYaw, 0.f));
	}
}
