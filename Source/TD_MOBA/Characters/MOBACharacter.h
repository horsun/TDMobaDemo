// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MOBACharacter.generated.h"

UCLASS()
class TD_MOBA_API AMOBACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMOBACharacter();

	/**
	*Character的属性获取 GDAttributeSetBase??
	*/
	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetMoveSpeed() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void CursorOverEvent(AActor* touchedActor);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
