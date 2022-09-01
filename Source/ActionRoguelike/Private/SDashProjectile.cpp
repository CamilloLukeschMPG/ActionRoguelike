// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASDashProjectile::ASDashProjectile()
{
}

// Called when the game starts or when spawned
void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASDashProjectile::Explode);
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, Delegate, 0.2f, false);
}


void ASDashProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	Explode();
}

void ASDashProjectile::Explode()
{
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASDashProjectile::TeleportInstigator);
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, Delegate, 0.2f, false);


	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
}

void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
	//GetInstigator()->SetActorLocation(GetActorLocation());

	GetWorld()->DestroyActor(this);
}