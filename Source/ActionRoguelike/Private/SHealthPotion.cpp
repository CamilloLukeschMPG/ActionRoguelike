// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"

ASHealthPotion::ASHealthPotion()
{
	HealAmount = 20.0f;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	AActor* OtherActor = Cast<AActor>(InstigatorPawn);
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp)
	{
		if (AttributeComp->Health < AttributeComp->MaxHealth)
		{
			AttributeComp->ApplyHealthChange(HealAmount);
			
			TriggerPickupTimer();
		}
	}
}