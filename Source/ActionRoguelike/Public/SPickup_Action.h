// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupBase.h"
#include "SPickup_Action.generated.h"

class USAction;

UCLASS()
class ACTIONROGUELIKE_API ASPickup_Action : public ASPickupBase
{
	GENERATED_BODY()
public:

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditAnywhere, Category = "Pickup")
	TArray<TSubclassOf<USAction>> ActionsToGrant;
};
