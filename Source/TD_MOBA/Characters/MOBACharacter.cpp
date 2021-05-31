// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBACharacter.h"

// Sets default values
AMOBACharacter::AMOBACharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

int32 AMOBACharacter::GetCharacterLevel() const
{
	return 0;
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

// Called when the game starts or when spawned
void AMOBACharacter::BeginPlay()
{
	Super::BeginPlay();
	OnBeginCursorOver.AddDynamic(this,&AMOBACharacter::CursorOverEvent);
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
