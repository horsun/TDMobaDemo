// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "AbilitySystemComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	{
		SpringArm->TargetArmLength = 800.f;
		SpringArm->SetRelativeRotation({-50, 0, 0});
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
	}
	MobaAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	MobaAbilitySystemComponent->SetIsReplicated(true);
	MOBAAttributeSet = CreateDefaultSubobject<UTDMOBAAttribute>(TEXT("MOBAAttributeSet"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return MobaAbilitySystemComponent;
}

int32 ABaseCharacter::GetCharacterLevel() const
{
	return CharacterLevel;
}

void ABaseCharacter::SetCharacterLevel(int32 TargetLevel)
{
	CharacterLevel = TargetLevel;
}

float ABaseCharacter::GetHealth() const
{
	return MOBAAttributeSet->GetHealth();
}

float ABaseCharacter::GetMaxHealth() const
{
	return MOBAAttributeSet->GetMaxHealth();
}

float ABaseCharacter::GetMana() const
{
	return MOBAAttributeSet->GetMana();
}

float ABaseCharacter::GetMaxMana() const
{
	return MOBAAttributeSet->GetMaxMana();
}

float ABaseCharacter::GetMoveSpeed() const
{
	return MOBAAttributeSet->GetMoveSpeed();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
