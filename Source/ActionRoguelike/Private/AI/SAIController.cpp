// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, L"Behaviour Tree is nullptr! Please assign BehaviourTree in your AI controller!"))
	{
		RunBehaviorTree(BehaviorTree);
	}

	//APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//if (ensure(MyPawn))
	//{
	//	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	//	GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
	//}
}

