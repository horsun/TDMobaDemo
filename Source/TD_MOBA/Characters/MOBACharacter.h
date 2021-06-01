// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "MOBACharacter.generated.h"


UENUM()
enum class ESkillKeyMap:uint8
{
	ESkillKeyMap_AbilityQ=0,
	ESkillKeyMap_AbilityW,
	ESkillKeyMap_AbilityE,
	ESkillKeyMap_AbilityR,
};


UCLASS()
class TD_MOBA_API AMOBACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMOBACharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	*Character的属性获取 GDAttributeSetBase??
	*/
	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性") //等级
	virtual int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category ="MOBA|角色|属性")
	virtual void SetCharacterLevel(int32 TargetLevel);

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性") //生命
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性") //法力值
	virtual float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性") //移速
	virtual float GetMoveSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float GetAttackSpeed() const;
	
	UFUNCTION(BlueprintCallable, Category = "MOBA|角色|属性")
	virtual float SetAttackSpeed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void CursorOverEvent(AActor* touchedActor);

	UPROPERTY(EditAnywhere, Replicated)
	int32 CharacterLevel = 1;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite)
	TMap<ESkillKeyMap, TSubclassOf<UBaseAbility>> MobaAbilityMap;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void test()
	{
		UE_LOG(LogTemp, Warning, TEXT("test"));
	};
};
