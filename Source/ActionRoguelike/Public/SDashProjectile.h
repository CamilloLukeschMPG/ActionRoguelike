// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASDashProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:

	FTimerHandle TimerHandle_Explode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* HitEffect;

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void Explode();

	void TeleportInstigator();

};
