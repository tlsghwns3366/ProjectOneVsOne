// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Character/EnemyCharacter.h"
#include "Controller/EnemyController.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Enemy->SetTarget(Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("Target")));
	Enemy->Attack();

	return EBTNodeResult::Succeeded;
}
