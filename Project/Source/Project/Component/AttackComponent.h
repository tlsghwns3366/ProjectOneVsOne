// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AProjectCharacter* Character;
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UProjectAnimInstance* Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UseStamaina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ComboAttackScale;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* WeaponAttackMontage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* KickMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> HitActorArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> ActorsToIgnore;

	FTimerHandle AttackTraceLoop;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION()
	void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


	void Attack();
	void KickAttack();

	void TraceStart();
	void KickTraceStart();
	void Trace();
	void KickTrace();
	void AttackDamage();
	void ClearAttack();
	bool PlayMontage(UAnimMontage* Montage);



};
