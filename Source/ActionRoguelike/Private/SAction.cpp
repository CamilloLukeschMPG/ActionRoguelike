// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "Components/ActorComponent.h"

void USAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, L"Started: %s", *GetNameSafe(this));
}

void USAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, L"Stopped: %s", *GetNameSafe(this));
}

UWorld* USAction::GetWorld() const
{
	if (UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp->GetWorld();
	}

	return nullptr;
}