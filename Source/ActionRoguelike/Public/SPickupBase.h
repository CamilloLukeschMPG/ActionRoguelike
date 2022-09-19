// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickupBase.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPickupBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickupBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RespawnTime;

	FTimerHandle TimerHandle_Respawn;

	void TriggerPickupTimer();
	void Respawn();

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive;

	void SetIsActive(bool IsActive);

	UFUNCTION()
	void OnRep_IsActive();
};
