// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealSelf.h"

#include "SAttributeComponent.h"
#include "AIModule/Classes/AIController.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"


USBTTask_HealSelf::USBTTask_HealSelf()
{
	HealPercentage = 0.2f;;
}

EBTNodeResult::Type USBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());

		if (!MyPawn)
		{
			return EBTNodeResult::Failed;
		}

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensureMsgf(AttributeComp, L"Heal task can't find AttributeComponent on Character!"))
		{
			AttributeComp->ApplyHealthChange(AttributeComp->MaxHealth * HealPercentage);
			DrawDebugString(GetWorld(), AttributeComp->GetOwner()->GetActorLocation(), "Healed!", nullptr, FColor::White, 4.0f, true);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}


