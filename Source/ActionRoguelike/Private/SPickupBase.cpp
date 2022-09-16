// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
ASPickupBase::ASPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	RespawnTime = 10.0f;

	SetReplicates(true);
}

void ASPickupBase::TriggerPickupTimer()
{
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASPickupBase::Respawn);
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, Delegate, RespawnTime, false);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(false);
}

void ASPickupBase::Respawn()
{
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetVisibility(true);
}
