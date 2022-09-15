// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SActionEffect_Buff_Thorns.generated.h"

class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API USActionEffect_Buff_Thorns : public USActionEffect
{
	GENERATED_BODY()
public:

	USActionEffect_Buff_Thorns();

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;


protected:
	UPROPERTY(EditAnywhere, Category = "Action")
	float DamageReflectFactor;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

};
