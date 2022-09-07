// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"

ASHealthPotion::ASHealthPotion()
{
	HealAmount = 20.0f;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	ensure(InstigatorPawn);
	AActor* OtherActor = Cast<AActor>(InstigatorPawn);
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(OtherActor);

	if (AttributeComp)
	{
		if (AttributeComp->ApplyHealthChange(this, HealAmount))
		{
			TriggerPickupTimer();
		}
	}
}