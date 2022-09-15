// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "SActionComponent.h"
#include "Components/ActorComponent.h"


void USAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, L"Started: %s", *GetNameSafe(this));

	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, L"Stopped: %s", *GetNameSafe(this));

	ensureAlways(bIsRunning);
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

bool USAction::CanStart_Implementation(AActor* InstigatorActor)
{
	return !IsRunning() && !GetOwningComponent()->ActiveGameplayTags.HasAny(BlockedTags);
}

UWorld* USAction::GetWorld() const
{
	if (UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp->GetWorld();
	}

	return nullptr;
}


bool USAction::IsRunning() const
{
	return bIsRunning;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}
