// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "Components/WidgetComponent.h"

#include "Widget/DamageWidget.h"

// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UUserWidget>BlueprintWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_DamageWidget.WBP_DamageWidget_C'"));
	if (BlueprintWidget.Succeeded())
	{
		Widget = BlueprintWidget.Class;
	}
	DamageWidget = Cast<UDamageWidget>(CreateWidget<UUserWidget>(GetWorld(), Widget));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));

	SetRootComponent(WidgetComponent);
	WidgetComponent->SetWidget(DamageWidget);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(100.f, 50.f));
}

// Called when the game starts or when spawned
void ADamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageActor::SetDamage(float Value)
{
	if (Value == 0.f)
	{
		if (DamageWidget)
		{
			DamageWidget->SetDamageText(FText::FromString("Block"));
		}
	}
	else
	{
		if (DamageWidget)
		{
			DamageWidget->SetDamageText(FText::AsNumber(Value));
		}
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &ADamageActor::ActorDestroy, 2.f, false);
}

void ADamageActor::ActorDestroy()
{
	Destroy();
}

