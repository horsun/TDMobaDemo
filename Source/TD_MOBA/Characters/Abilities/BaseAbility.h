// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class TD_MOBA_API UBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage * AbilityMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GamePlayEffect;
};
