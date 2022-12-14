// Fill out your copyright notice in the Description page of Project Settings.


#include "SAnimInstance.h"

#include "SActionComponent.h"
#include "GameplayTagContainer.h"

void USAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		ActionComp = Cast<USActionComponent>(OwningActor->GetComponentByClass(USActionComponent::StaticClass()));
	}
}

void USAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status.Stunned");

	if (ActionComp)
	{
		bIsStunned = ActionComp->ActiveGameplayTags.HasTag(StunnedTag);
	}
}
