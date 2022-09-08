// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "TimerManager.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"
#include "Curves/CurveFloat.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"


ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASGameModeBase::SpawnBotTimerElapsed);
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, Delegate, SpawnTimerInterval, true);
}

void ASGameModeBase::KillAll()
{
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		if (USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot))
		{
			AttributeComp->Kill(this); //TODOcl: pass in player for kill credit?
		}
	}
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	int32 NrOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		if (USAttributeComponent::IsActorAlive(Bot))
		{
			NrOfAliveBots++;
		}
	}

	float MaxBotCount = DifficultyCurve ? DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds) : 10.0f;

	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, L"max bot count reached, skipping bot spawn.");
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensureMsgf(QueryInstance, L"Please set a bot spawning query in the game mode!"))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, L"Spawn bot EQS Query Failed!");
		return;
	}




	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.Num())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0] + FVector(0.f,0.f, 50.0f), FRotator::ZeroRotator, SpawnParams);
		DrawDebugSphere(GetWorld(), Locations[0] + FVector(0.f, 0.f, 50.0f), 50.f, 20, FColor::Blue, false, 60.f);
	}

}
