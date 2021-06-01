// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBACharacter.h"
#include "MOBAEnemy.generated.h"

UCLASS()
class TD_MOBA_API AMOBAEnemy : public AMOBACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMOBAEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

};
