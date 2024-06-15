// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Blocking.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Controller/EnemyController.h"
#include "Character/EnemyCharacter.h"
UBTTask_Blocking::UBTTask_Blocking()
{
	NodeName = TEXT("Blocking");
	bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_Blocking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	SetNextTickTime(NodeMemory, RemainingWaitTime);

	if (AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Character->SetBlocking(true);
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_Blocking::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ensure(GetSpecialNodeMemory<FBTTaskMemory>(NodeMemory)->NextTickRemainingTime <= 0.f);

	if (AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Character->SetBlocking(false);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
void UBTTask_Blocking::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTTaskMemory* TaskMemory = GetSpecialNodeMemory<FBTTaskMemory>(NodeMemory);
	if (TaskMemory->NextTickRemainingTime)
	{
		Values.Add(FString::Printf(TEXT("remaining: %ss"), *FString::SanitizeFloat(TaskMemory->NextTickRemainingTime)));
	}
}

FString UBTTask_Blocking::GetStaticDescription() const
{
	if (FMath::IsNearlyZero(RandomDeviation))
	{
		return FString::Printf(TEXT("%s: %.1fs"), *Super::GetStaticDescription(), WaitTime);
	}
	else
	{
		return FString::Printf(TEXT("%s: %.1f+-%.1fs"), *Super::GetStaticDescription(), WaitTime, RandomDeviation);
	}
}

EBTNodeResult::Type UBTTask_Blocking::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Character->SetBlocking(false);
	}
	return EBTNodeResult::Failed;
}
