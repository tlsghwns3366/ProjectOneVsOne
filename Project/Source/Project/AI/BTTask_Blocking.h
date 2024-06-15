// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Blocking.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_Blocking : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Blocking();
public:
	UPROPERTY(Category = Time, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float WaitTime;

	UPROPERTY(Category = Time, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
	float RandomDeviation;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;
};
