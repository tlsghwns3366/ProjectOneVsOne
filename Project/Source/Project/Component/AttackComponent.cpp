// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttackComponent.h"
#include "DamageType_Physical.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include "CharacterStateComponent.h"
#include "ProjectAnimInstance.h"
#include "Character/ProjectCharacter.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AProjectCharacter>(GetOwner());
	Anim = Cast<UProjectAnimInstance>(Character->GetMesh()->GetAnimInstance());
	if (Anim)
	{
		Anim->OnPlayMontageNotifyBegin.AddDynamic(this, &UAttackComponent::OnNotifyBeginReceived);
		Anim->OnMontageEnded.AddDynamic(this, &UAttackComponent::OnAttackMontageEnded);
		Anim->AttackStartTrace.AddUObject(this, &UAttackComponent::TraceStart);
		Anim->AttackKickTrace.AddUObject(this, &UAttackComponent::KickTraceStart);
	}
	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackComponent::OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	ComboAttackScale++;
	AttackIndex--;
	if (AttackIndex < 0)
	{
		AttackIndex = 0;
		ClearAttack();
	}
	ActorsToIgnore.Empty();
	GetWorld()->GetTimerManager().ClearTimer(AttackTraceLoop);
}

void UAttackComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ClearAttack();
}

void UAttackComponent::Attack()
{
	if (Anim->IsBlocking|| Anim->IsFalling || WeaponAttackMontage == nullptr)
	{
		return;
	}
	if (Anim)
	{
		if (!Anim->Montage_IsPlaying(WeaponAttackMontage))
		{
			AttackIndex = 0;
			ComboAttackScale = 1.f;
			Anim->IsAttack = true;
			PlayMontage(WeaponAttackMontage);
			ActorsToIgnore.Empty();
		}
		else
		{
			AttackIndex = 1;
		}
	}

}

void UAttackComponent::KickAttack()
{
	if (Anim->IsBlocking || Anim->IsFalling || KickMontage == nullptr)
	{
		return;
	}
	if (Anim)
	{
		if (!Anim->Montage_IsPlaying(KickMontage))
		{
			AttackIndex = 0;
			ComboAttackScale = 1.f;
			Anim->IsAttack = true;
			PlayMontage(KickMontage);
			ActorsToIgnore.Empty();
		}
		else
		{
			AttackIndex = 1;
		}
	}

}

void UAttackComponent::TraceStart()
{
	GetWorld()->GetTimerManager().SetTimer(AttackTraceLoop, this, &UAttackComponent::Trace, 0.01f, true);
}

void UAttackComponent::KickTraceStart()
{
	GetWorld()->GetTimerManager().SetTimer(AttackTraceLoop, this, &UAttackComponent::KickTrace, 0.01f, true);
}

void UAttackComponent::Trace()
{
	FVector StartPoint = Character->CharacterWeapon->GetSocketLocation("StartPoint");
	FVector EndPoint = Character->CharacterWeapon->GetSocketLocation("EndPoint");

	ActorsToIgnore.AddUnique(GetOwner());

	FHitResult HitResult;
	bool Result;
	Result = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		StartPoint,
		EndPoint,
		5.0f,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.0f
	);
	if (Result)
	{
		HitActorArray.AddUnique(HitResult.GetActor());
		AttackDamage();
	}
}

void UAttackComponent::KickTrace()
{
	FVector StartPoint = Character->GetMesh()->GetSocketLocation("foot_l_SocketStart");
	FVector EndPoint = Character->GetMesh()->GetSocketLocation("foot_l_SocketEnd");

	ActorsToIgnore.AddUnique(GetOwner());

	FHitResult HitResult;
	bool Result;
	Result = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		StartPoint,
		EndPoint,
		5.0f,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.0f
	);
	if (Result)
	{
		HitActorArray.AddUnique(HitResult.GetActor());
		AttackDamage();
	}
}

void UAttackComponent::AttackDamage()
{
	for (AActor* HitActor : HitActorArray)
	{
		float Damage = Character->CharacterState->CurrentState.Damage * ComboAttackScale;
		Damage = FMath::FRandRange(Damage * 0.85f, Damage * 1.15f);
		Damage = FMath::RoundFromZero(Damage);

		TSubclassOf<UDamageType_Physical> DamageTypeClass = UDamageType_Physical::StaticClass();
		UGameplayStatics::ApplyDamage(HitActor, Damage, Character->GetController(), Character, DamageTypeClass);
		ActorsToIgnore.AddUnique(HitActor);
	}
	HitActorArray.Empty();
}

void UAttackComponent::ClearAttack()
{
	if (Anim)
	{
		Anim->IsAttack = false;
		Anim->Montage_Stop(0.f, WeaponAttackMontage);
		Anim->Montage_Stop(0.f, KickMontage);
	}
	Character->SetKick(false);
	GetWorld()->GetTimerManager().ClearTimer(AttackTraceLoop);
}

bool UAttackComponent::PlayMontage(UAnimMontage* Montage)
{
	if (Montage)
	{
		const float PlayRate = 1.0f;
		bool bPlayedSuccessfully = Character->PlayAnimMontage(Montage, PlayRate) > 0.0f;
		return bPlayedSuccessfully;
	}
	else
		return false;
}
