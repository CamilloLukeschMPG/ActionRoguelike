// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "SActionComponent.h"
#include "ActionRoguelike/ActionRoguelike.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"

void USAction::Initialize(USActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

void USAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, L"Started: %s", *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(L"Started: %s", *ActionName.ToString()), FColor::Green);

	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantsTags);
	RepData = { true, InstigatorActor };

	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this);

	if (GetOwningComponent()->GetOwnerRole() == ROLE_Authority)
	{
		TimeStarted = GetWorld()->TimeSeconds;
	}
}

void USAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, L"Stopped: %s", *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(L"Stopped: %s", *ActionName.ToString()), FColor::White);

	//ensureAlways(bIsRunning);

	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantsTags);
	RepData = { false, InstigatorActor };
	
	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this);
}

bool USAction::CanStart_Implementation(AActor* InstigatorActor)
{
	return !IsRunning() && !GetOwningComponent()->ActiveGameplayTags.HasAny(BlockedTags);
}


UWorld* USAction::GetWorld() const
{
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}


bool USAction::IsRunning() const
{
	return RepData.bIsRunning;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return ActionComp;
}

void USAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

void USAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAction, RepData);
	DOREPLIFETIME(USAction, TimeStarted);
	DOREPLIFETIME(USAction, ActionComp);
}