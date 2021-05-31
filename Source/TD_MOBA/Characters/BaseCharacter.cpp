// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

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
		SpringArm->SetRelativeRotation({-50,0,0});
	}
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return MobaAbilitySystemComponent;
}

int32 ABaseCharacter::GetCharacterLevel() const
{
	return 0;
}

float ABaseCharacter::GetHealth() const
{
	return 0.f;
}

float ABaseCharacter::GetMaxHealth() const
{
	return  0.f;
}

float ABaseCharacter::GetMana() const
{
	return 0.f;
}

float ABaseCharacter::GetMaxMana() const
{
	return  0.f;
}

float ABaseCharacter::GetMoveSpeed() const
{
	return 0.f;
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

