// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacter.generated.h"


UCLASS()
class TD_MOBA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	/**
	 *重载获取GASCompon
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	/**
	 *Character的属性获取 GDAttributeSetBase??
	 */
	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")

	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	float GetMoveSpeed() const;
	// UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	// float GetStamina() const;
	//
	// UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	// float GetMaxStamina() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAbilitySystemComponent* MobaAbilitySystemComponent = nullptr;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
