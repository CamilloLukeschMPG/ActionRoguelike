// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "ActionRoguelike/ActionRoguelike.h"
#include "Net/UnrealNetwork.h"
#include "SSaveGame.h"

ASPlayerState::ASPlayerState()
{
	CreditScore = 0;

	SetReplicates(true);
}

ASPlayerState* ASPlayerState::GetPlayerStateFromActor(AActor* FromActor)
{
	if (ACharacter* Character = Cast<ACharacter>(FromActor))
	{
		return Cast<ASPlayerState>(Character->GetPlayerState());
	}
	else if (APlayerController* Controller = Cast<APlayerController>(FromActor))
	{
		return Controller->GetPlayerState<ASPlayerState>();
	}

	return nullptr;
}

bool ASPlayerState::ApplyCreditScoreChange(AActor* InstigatorActor, int32 Delta)
{
	if (Delta && CreditScore + Delta < 0)
	{
		return false;
	}

	CreditScore += Delta;

	ensure(!GetWorld()->IsNetMode(NM_Client));
	OnCreditScoreChanged.Broadcast(this, CreditScore, Delta);
	MulticastCreditScoreChanged(CreditScore, Delta);
	return true;
}

int32 ASPlayerState::GetCreditScore() const
{
	return CreditScore;
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->CreditScore = CreditScore;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		CreditScore = SaveObject->CreditScore;
	}
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, CreditScore);
}

void ASPlayerState::MulticastCreditScoreChanged_Implementation(float NewCreditScore, float Delta)
{
	LogOnScreen(this, FString::Printf(L"Broadcasting Credit score change on: %s", *GetNameSafe(this)), FColor::Orange);
	OnCreditScoreChanged.Broadcast(this, NewCreditScore, Delta);
}