// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"
#include "GameFramework/Pawn.h"


#define LOCTEXT_NAMESPACE "InteractableActors"

ASHealthPotion::ASHealthPotion()
{
	HealAmount = 20.0f;
	CreditScoreCost = 15;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	ensure(InstigatorPawn);

	ASPlayerState* PlayerState = ASPlayerState::GetPlayerStateFromActor(InstigatorPawn);

	if (PlayerState->GetCreditScore() >= CreditScoreCost)
	{
		if (USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn))
		{
			if (AttributeComp->ApplyHealthChange(this, HealAmount))
			{
				PlayerState->ApplyCreditScoreChange(this, -CreditScoreCost);
				TriggerPickupTimer();
			}
		}
	}
}

FText ASHealthPotion::GetInteractText_Implementation(APawn * InstigatorPawn)
{
	if (USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn))
	{
		if (AttributeComp->GetHealthPercentage() == 1.0f)
		{
			return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
		}
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Costs{0} Credits.Restores health to maximum."), CreditScoreCost);
}

#undef LOCTEXT_NAMESPACE 