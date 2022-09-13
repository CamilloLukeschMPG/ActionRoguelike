// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditScoreChanged, AActor*, InstigatorActor, int32, NewCreditScore, int32, Delta);


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

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Credits")
	int32 CreditScore;

};
