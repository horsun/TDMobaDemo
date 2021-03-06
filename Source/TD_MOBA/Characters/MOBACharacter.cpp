// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBACharacter.h"

// Sets default values
AMOBACharacter::AMOBACharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MobaAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	MobaAbilitySystemComponent->SetIsReplicated(true);
	MOBAAttributeSet = CreateDefaultSubobject<UTDMOBAAttribute>(TEXT("MOBAAttributeSet"));
}

UAbilitySystemComponent* AMOBACharacter::GetAbilitySystemComponent() const
{
	return MobaAbilitySystemComponent;
}

void AMOBACharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

int32 AMOBACharacter::GetCharacterLevel() const
{
	return 0;
}

void AMOBACharacter::SetCharacterLevel(int32 TargetLevel)
{
	CharacterLevel = TargetLevel;
}

float AMOBACharacter::GetHealth() const
{
	return 0.f;
}

float AMOBACharacter::GetMaxHealth() const
{
	return 0.f;
}

float AMOBACharacter::GetMana() const
{
	return 0.f;
}

float AMOBACharacter::GetMaxMana() const
{
	return 0.f;
}

float AMOBACharacter::GetMoveSpeed() const
{
	return 0.f;
}

void AMOBACharacter::SetMoveSpeed() const
{
}

float AMOBACharacter::GetAttackSpeed() const
{
	return 0.f;
}

void AMOBACharacter::SetAttackSpeed() const
{
}

bool AMOBACharacter::IsDie() const
{
	return false;
}

// Called when the game starts or when spawned
void AMOBACharacter::BeginPlay()
{
	Super::BeginPlay();
	OnBeginCursorOver.AddDynamic(this, &AMOBACharacter::CursorOverEvent);
	//在游戏开始的时候赋予角色对应的能力
	for (auto it = MobaAbilityMap.CreateIterator(); it; ++it)
	{
		MobaAbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(it.Value())
		);
	}
}

void AMOBACharacter::CursorOverEvent(AActor* touchedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Character On Over"));
}

// Called every frame
void AMOBACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMOBACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
