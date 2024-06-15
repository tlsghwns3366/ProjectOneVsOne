// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "MotionWarpingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"


#include "Widget/EnemyStateWidget.h"
#include "ProjectStateBase.h"
#include "ProjectAnimInstance.h"
#include "Component/AttackComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>BlueprintWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_EnemyState.WBP_EnemyState_C'"));
	if (BlueprintWidget.Succeeded())
	{
		Widget = BlueprintWidget.Class;
	}

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(200.f, 30.f));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	EnemyStateWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
	WidgetComponent->SetWidget(EnemyStateWidget);
	if (UEnemyStateWidget* State = Cast<UEnemyStateWidget>(EnemyStateWidget))
	{
		State->SetCharacter(this);
	}
}

void AEnemyCharacter::Attack()
{
	if (Anim->Montage_IsPlaying(RollingMontage) || Anim->IsFalling || Anim->IsStun)
		return;
	if (Target)
	{


		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
		LookAtRotation.Pitch = 0.f;
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("AttackLocation", GetActorLocation(), LookAtRotation);

	}
	else
	{
		FRotator NewRotation;
		NewRotation.Yaw += GetControlRotation().Yaw;
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("AttackLocation", GetActorLocation(), NewRotation);
	}	
	AttackComponent->Attack();
}

void AEnemyCharacter::CharacterDie()
{
	Super::CharacterDie();
	AAIController* EnemyController = Cast<AAIController>(GetController());
	if (EnemyController)
	{
		EnemyController->GetBrainComponent()->StopLogic(FString("Die"));
		EnemyController->Destroy();
	}
	AProjectStateBase* ProjectState =Cast<AProjectStateBase>(GetWorld()->GetGameState());
	if (ProjectState)
	{
		ProjectState->PlayerEndText(FText::FromString("Player Win"));
	}
}

void AEnemyCharacter::SetStun()
{
	SetBlocking(false);
	Anim->IsStun = true;
	AttackComponent->ClearAttack();
	AAIController* MyController = Cast<AAIController>(GetController());
	MyController->GetBlackboardComponent()->SetValueAsBool("IsStun", true);
	GetWorld()->GetTimerManager().SetTimer(StunTimer,this, &AEnemyCharacter::SetStunTimer, 3.f, false);

}

void AEnemyCharacter::SetTarget(AActor* Actor)
{
	Target = Actor;
}

void AEnemyCharacter::SetStunTimer()
{
	Anim->IsStun = false;
	AAIController* MyController = Cast<AAIController>(GetController());
	MyController->GetBlackboardComponent()->SetValueAsBool("IsStun", false);
}
