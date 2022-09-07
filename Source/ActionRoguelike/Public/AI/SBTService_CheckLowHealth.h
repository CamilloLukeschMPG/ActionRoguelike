// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h"
#include "AIModule/Classes/BehaviorTree/BTService.h"
#include "SBTService_CheckLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USBTService_CheckLowHealth : public UBTService
{
	GENERATED_BODY()

public:
	USBTService_CheckLowHealth();
protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector ShouldFindCoverKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthPercentage;

	UPROPERTY(EditAnywhere, Category = "AI")
	float HighHealthPercentage;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
