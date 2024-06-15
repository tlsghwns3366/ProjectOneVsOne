// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyController();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerceptionComponent;
	UPROPERTY(EditAnywhere)
	class UAISenseConfig_Sight* SightConfig;


	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere)
	class UBlackboardData* BlackboardData;


public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void SenseDetected(AActor* Actor, FAIStimulus const Stimulus);
};
