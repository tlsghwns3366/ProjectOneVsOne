// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectCharacter.generated.h"

UCLASS()
class PROJECT_API AProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectCharacter();
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCharacterStateComponent* CharacterState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAttackComponent* AttackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* CharacterWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UProjectAnimInstance* Anim;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* RollingMontage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* BlookingHitMontage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* HitMontage = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsDie = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBlocking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCounter = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsKick = false;

	FTimerHandle KickTimer;
	FTimerHandle CounterTimer;
	FTimerHandle StunTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void Attack();
	virtual void KickAttack();
	virtual void JumpStart();
	virtual void JumpEnd();
	virtual void CharacterDie();
	virtual void SetBlocking(bool Value);
	virtual void Rolling();
	virtual void SetStun();
	void SetKick(bool Value);
};
