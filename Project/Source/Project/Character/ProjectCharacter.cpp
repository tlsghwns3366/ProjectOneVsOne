// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/CapsuleComponent.h"

#include "Component/DamageInterface.h"
#include "Component/CharacterStateComponent.h"
#include "Component/AttackComponent.h"
#include "ProjectAnimInstance.h"

// Sets default values
AProjectCharacter::AProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f); // ...at this rotation rate

	CharacterState = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("CharacterState"));
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	CharacterWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterWeapon"));
}

// Called when the game starts or when spawned
void AProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	Anim = Cast<UProjectAnimInstance>(GetMesh()->GetAnimInstance());
	CharacterWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_Socket_Hand_r");
	
}

// Called every frame
void AProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AProjectCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (!Anim->Montage_IsPlaying(AttackComponent->WeaponAttackMontage) || !Anim->Montage_IsPlaying(AttackComponent->KickMontage))
	{
		if (Anim->IsBlocking)
		{
			if (Cast<AProjectCharacter>(DamageCauser)->IsKick)
			{
				SetStun();
				Damage = 1.f;
			}
			else
			{
				PlayAnimMontage(BlookingHitMontage, 1.f);
				Damage = 0.f;
			}
		}
		else
			PlayAnimMontage(HitMontage, 1.f);
	}
	if (IsCounter)
	{
		Cast<AProjectCharacter>(DamageCauser)->SetStun();
		Damage = 0.f;
	}

	if (IDamageInterface* DamageInterface = Cast<IDamageInterface>(DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>()))
	{
		IsDie = !DamageInterface->SetAttackType(CharacterState, Damage);
	}
	if (IsDie)
	{
		CharacterDie();
	}
	return 0.0f;
}

void AProjectCharacter::Attack()
{
	if (Anim->Montage_IsPlaying(RollingMontage) || Anim->IsFalling || Anim->IsStun)
		return;
	if(Anim->Montage_IsPlaying(HitMontage))
		Anim->Montage_Stop(1.f,HitMontage);

	FRotator NewRotation;
	NewRotation.Yaw += GetControlRotation().Yaw;
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("AttackLocation", GetActorLocation(), NewRotation);
	AttackComponent->Attack();
}

void AProjectCharacter::KickAttack()
{
	if (Anim->Montage_IsPlaying(RollingMontage) || Anim->IsFalling || Anim->IsStun)
		return;
	if (Anim->Montage_IsPlaying(HitMontage))
		Anim->Montage_Stop(1.f, HitMontage);
	FRotator NewRotation;
	SetKick(true);
	NewRotation.Yaw += GetControlRotation().Yaw;
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("AttackLocation", GetActorLocation(), NewRotation);
	AttackComponent->KickAttack();
}

void AProjectCharacter::JumpStart()
{
	if (Anim->Montage_IsPlaying(RollingMontage) || Anim->IsAttack)
		return;

	Jump();
}

void AProjectCharacter::JumpEnd()
{
	StopJumping();
}

void AProjectCharacter::CharacterDie()
{
	GetMesh()->SetSimulatePhysics(true);
	UCapsuleComponent* CharacterCapsule = GetCapsuleComponent();
	if (CharacterCapsule)
	{
		CharacterCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AProjectCharacter::SetBlocking(bool Value)
{
	if (Anim->IsStun)
		return;
	if (Anim->Montage_IsPlaying(HitMontage))
		Anim->Montage_Stop(1.f, HitMontage);

	if (!Anim->Montage_IsPlaying(RollingMontage))
	{
		if (!IsBlocking && Value)
		{
			IsCounter = true;
			GetWorld()->GetTimerManager().SetTimer(CounterTimer, [&]() {
				IsCounter = false;
				}, 0.5, false);
		}
		IsBlocking = Value;
		Anim->IsBlocking = Value;
		AttackComponent->ClearAttack();
	}
}

void AProjectCharacter::Rolling()
{
	if (Anim->IsStun)
		return;

	if (!Anim->Montage_IsPlaying(RollingMontage) && !Anim->IsFalling)
	{
		Anim->IsBlocking = false;
		FVector MovementDirection = FVector(Anim->ForwardInput, Anim->SideInput, 0.0f).GetSafeNormal();
		FRotator NewRotation = MovementDirection.Rotation();
		NewRotation.Yaw += GetControlRotation().Yaw;
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("Rolling", GetActorLocation(), NewRotation);
		AttackComponent->ClearAttack();
		PlayAnimMontage(RollingMontage, 1.0f);
	}
}

void AProjectCharacter::SetStun()
{
	SetBlocking(false);
	Anim->IsStun = true;
	AttackComponent->ClearAttack();
	GetWorld()->GetTimerManager().SetTimer(StunTimer, [&]() {
		Anim->IsStun = false;
		}, 3.f, false);
}

void AProjectCharacter::SetKick(bool Value)
{
	IsKick = Value;
}
