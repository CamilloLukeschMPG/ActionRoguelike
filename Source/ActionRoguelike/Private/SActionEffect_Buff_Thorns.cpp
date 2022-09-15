// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_Buff_Thorns.h"
#include "SAttributeComponent.h"

USActionEffect_Buff_Thorns::USActionEffect_Buff_Thorns()
{
	Duration = 0.0f;
	Period = 0.0f;
	DamageReflectFactor = 0.5f;
}

void USActionEffect_Buff_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	auto* Comp = USAttributeComponent::GetAttributes(Instigator);
	if (ensure(Comp))
	{
		Comp->OnHealthChanged.AddDynamic(this, &USActionEffect_Buff_Thorns::OnHealthChanged);
	}

}

void USActionEffect_Buff_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	auto* Comp = USAttributeComponent::GetAttributes(Instigator);
	if (ensure(Comp))
	{
		Comp->OnHealthChanged.RemoveDynamic(this, &USActionEffect_Buff_Thorns::OnHealthChanged);
	}
}

void USActionEffect_Buff_Thorns::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		auto* InstigatorAttributeComp = USAttributeComponent::GetAttributes(InstigatorActor);
		InstigatorAttributeComp->ApplyHealthChange(OwningComp->GetOwner(), float(int32((Delta * DamageReflectFactor) + 0.5f)));
	}
}