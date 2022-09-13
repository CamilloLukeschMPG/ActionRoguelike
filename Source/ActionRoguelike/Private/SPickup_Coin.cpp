// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup_Coin.h"
#include "SPlayerState.h"
#include "GameFramework/Pawn.h"

ASPickup_Coin::ASPickup_Coin()
{
	CreditScoreValue = 5;
}

void ASPickup_Coin::Interact_Implementation(APawn* InstigatorPawn)
{
	ensure(InstigatorPawn);

	if (ASPlayerState* PlayerState = ASPlayerState::GetPlayerStateFromActor(InstigatorPawn))
	{
		if (PlayerState->ApplyCreditScoreChange(this, CreditScoreValue))
		{
			TriggerPickupTimer();
		}
	}
}
