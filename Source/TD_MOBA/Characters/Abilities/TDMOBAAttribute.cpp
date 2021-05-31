// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMOBAAttribute.h"


UTDMOBAAttribute::UTDMOBAAttribute()
: Health(1.f)
, MaxHealth(1.f)
, Mana(0.f)
, MaxMana(0.f)
, AttackPower(1.0f)
, DefensePower(1.0f)
, MoveSpeed(1.0f)
, Damage(0.0f)
{
}

void UTDMOBAAttribute::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UTDMOBAAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UTDMOBAAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTDMOBAAttribute, Health);
	DOREPLIFETIME(UTDMOBAAttribute, MaxHealth);
	DOREPLIFETIME(UTDMOBAAttribute, Mana);
	DOREPLIFETIME(UTDMOBAAttribute, MaxMana);
	DOREPLIFETIME(UTDMOBAAttribute, AttackPower);
	DOREPLIFETIME(UTDMOBAAttribute, DefensePower);
	DOREPLIFETIME(UTDMOBAAttribute, MoveSpeed);
}

void UTDMOBAAttribute::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, Health, OldValue);
}

void UTDMOBAAttribute::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, MaxHealth, OldValue);
}

void UTDMOBAAttribute::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, Mana, OldValue);
}

void UTDMOBAAttribute::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, MaxMana, OldValue);
}

void UTDMOBAAttribute::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, AttackPower, OldValue);
}

void UTDMOBAAttribute::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, DefensePower, OldValue);
}

void UTDMOBAAttribute::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDMOBAAttribute, MoveSpeed, OldValue);
}

