// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "MOBACharacter.h"
#include "Abilities/TDMOBAAttribute.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "BaseCharacter.generated.h"


UCLASS()
class TD_MOBA_API ABaseCharacter : public AMOBACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual int32 GetCharacterLevel() const override;

	virtual void SetCharacterLevel(int32 TargetLevel) override;

	virtual float GetHealth() const override;

	virtual float GetMaxHealth() const override;

	virtual float GetMana() const override;

	virtual float GetMaxMana() const override;

	virtual float GetMoveSpeed() const override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* MobaAbilitySystemComponent;
	
	UPROPERTY()
	UTDMOBAAttribute* MOBAAttributeSet;
	
	


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
