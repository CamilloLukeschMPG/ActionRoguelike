// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "GameFramework/Character.h"


ASPlayerState::ASPlayerState()
{
	CreditScore = 0;
}

ASPlayerState* ASPlayerState::GetPlayerStateFromActor(AActor* FromActor)
{
	if (ACharacter* Character = Cast<ACharacter>(FromActor))
	{
		return Cast<ASPlayerState>(Character->GetPlayerState());
	}

	return nullptr;
}

bool ASPlayerState::ApplyCreditScoreChange(AActor* InstigatorActor, int32 Delta)
{
	if (CreditScore + Delta < 0)
	{
		return false;
	}

	CreditScore += Delta;

	OnCreditScoreChanged.Broadcast(InstigatorActor, CreditScore, Delta);
	return true;
}

int32 ASPlayerState::GetCreditScore() const
{
	return CreditScore;
}
