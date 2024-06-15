// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Character/EnemyCharacter.h"

AEnemyController::AEnemyController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 3000.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 45.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;
		SightConfig->PointOfViewBackwardOffset = 150.f;
		SightConfig->NearClippingRadius = 150.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
		AIPerceptionComponent->ConfigureSense(*SightConfig);
	}
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::SenseDetected);
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BehaviorTree)
		RunBehaviorTree(BehaviorTree);
}

void AEnemyController::SenseDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	GetBlackboardComponent()->SetValueAsObject("Target", Actor);
}
