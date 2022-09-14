// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class USActionComponent;

UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StopAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;



protected:

	UFUNCTION(BlueprintCallable, Category = "Action")
	USActionComponent* GetOwningComponent() const;

	//Action can only start if OwningActor has none of these Tags applied
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	//Tags added to owning actor when activated, removed when action stops
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	bool bIsRunning;
};
