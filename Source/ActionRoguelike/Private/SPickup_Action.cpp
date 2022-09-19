// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup_Action.h"
#include "SAction.h"
#include "SActionComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"

void ASPickup_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn) || ActionsToGrant.IsEmpty())
	{
		return;
	}

	if (USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass())))
	{
		for (TSubclassOf<USAction> ActionClass : ActionsToGrant)
		{
			if (ActionComp->GetAction(ActionClass))
			{
				FString DebugMsg = FString::Printf(L"Action '%s' already known.", *GetNameSafe(ActionClass));
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
				continue;
			}

			ActionComp->AddAction(InstigatorPawn, ActionClass);
		}

		TriggerPickupTimer();
	}

}
