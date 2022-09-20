// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class USSaveGame;

UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:

	FString SlotName;

	UPROPERTY()
	USSaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float PlayerRespawnDelay;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

public:
	ASGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;


	virtual void StartPlay() override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;


	UFUNCTION(Exec)
	void KillAll();

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);


	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();
};
