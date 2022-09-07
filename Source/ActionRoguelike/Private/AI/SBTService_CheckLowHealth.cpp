// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USBTService_CheckLowHealth::USBTService_CheckLowHealth()
{
	HighHealthPercentage = 0.9f;
	LowHealthPercentage = 0.3f;
}

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComp))
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController))
		{
			APawn* Pawn = MyController->GetPawn();
			if (ensure(Pawn))
			{
				USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Pawn);
				if (ensure(AttributeComp))
				{
					bool bShouldFindCover = AttributeComp->GetHealthPercentage() <= LowHealthPercentage;

					bool const bCurrentlyFindingCover = BlackboardComp->GetValueAsBool(ShouldFindCoverKey.SelectedKeyName);

					if (bCurrentlyFindingCover)
					{
						bShouldFindCover = AttributeComp->GetHealthPercentage() < HighHealthPercentage;
					}
					
					BlackboardComp->SetValueAsBool(ShouldFindCoverKey.SelectedKeyName, bShouldFindCover);
				}
			}
		}

	}
}
