// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupBase.h"
#include "SPickup_Coin.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickup_Coin : public ASPickupBase
{
	GENERATED_BODY()
public:

	ASPickup_Coin();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditScoreValue;
};
