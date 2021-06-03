// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBAHero.h"
#include "AbilitySystemComponent.h"

// Sets default values
AMOBAHero::AMOBAHero()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;
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

}



int32 AMOBAHero::GetCharacterLevel() const
{
	return CharacterLevel;
}

void AMOBAHero::SetCharacterLevel(int32 TargetLevel)
{
	CharacterLevel = TargetLevel;
}

float AMOBAHero::GetHealth() const
{
	return MOBAAttributeSet->GetHealth();
}

float AMOBAHero::GetMaxHealth() const
{
	return MOBAAttributeSet->GetMaxHealth();
}

float AMOBAHero::GetMana() const
{
	return MOBAAttributeSet->GetMana();
}

float AMOBAHero::GetMaxMana() const
{
	return MOBAAttributeSet->GetMaxMana();
}

float AMOBAHero::GetMoveSpeed() const
{
	return MOBAAttributeSet->GetMoveSpeed();
}

void AMOBAHero::PossessedBy(AController* NewController)
{
}

// Called when the game starts or when spawned
void AMOBAHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMOBAHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMOBAHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
