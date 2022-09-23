// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class USActionComponent;
class UTexture2D;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;
};

UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(USActionComponent* NewActionComp);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart;

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


	virtual bool IsSupportedForNetworking() const override { return true; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UTexture2D* Icon;

	UFUNCTION(BlueprintCallable, Category = "Action")
	USActionComponent* GetOwningComponent() const;

	//Action can only start if OwningActor has none of these Tags applied
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTagContainer GrantsTags;

	//Tags added to owning actor when activated, removed when action stops
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData RepData;

	UPROPERTY(Replicated)
	USActionComponent* ActionComp;

	UFUNCTION()
	void OnRep_RepData();

	UPROPERTY(Replicated)
	float TimeStarted;

};
