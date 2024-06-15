// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ProjectAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FAttackStartTrace);
DECLARE_MULTICAST_DELEGATE(FAttackKickTrace);



UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_WeaponEquip UMETA(DisplayName = "WeaponEquip"),
};

UCLASS()
class PROJECT_API UProjectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	float	Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	float ForwardInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	float SideInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	float DeltaTimeX;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	bool	IsMoving;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	bool	IsFalling;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	bool	IsAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	bool	IsBlocking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	bool	IsStun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	class AProjectCharacter* Character;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	class	UCharacterMovementComponent* CharacterMovement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	FAttackStartTrace AttackStartTrace;
	FAttackKickTrace AttackKickTrace;

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void SetCharacterState();

	UFUNCTION()
	void AnimNotify_StartTrace();
	UFUNCTION()
	void AnimNotify_KickStart();

	void SetBlockRotation();

};
