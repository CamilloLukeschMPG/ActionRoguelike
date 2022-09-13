// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"
#include "GameFramework/Pawn.h"

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