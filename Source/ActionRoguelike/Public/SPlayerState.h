// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

class USSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditScoreChanged, ASPlayerState*, PlayerState, int32, NewCreditScore, int32, Delta);


UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	ASPlayerState();

	UFUNCTION(BlueprintPure, Category = "Credits")
	static ASPlayerState* GetPlayerStateFromActor(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Credits")
	bool ApplyCreditScoreChange(AActor* InstigatorActor, int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetCreditScore() const;

	UPROPERTY(BlueprintAssignable, Category = "Credits")
	FOnCreditScoreChanged OnCreditScoreChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Credits")
	int32 CreditScore;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastCreditScoreChanged(float NewCreditScore, float Delta);

};
