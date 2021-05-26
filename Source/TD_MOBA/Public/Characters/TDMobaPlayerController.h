// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Managers/TDMobaPlayerCameraManager.h"
#include "TDMobaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TD_MOBA_API ATDMobaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	explicit ATDMobaPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	
	void SetDestination_Pressed();
	
	void SetDestination_Released();
	
	void ViewerSwitch();
	
	void StopAction();
	void FindPawn_Pressed();
	void FindPawn_Released();


	void MoveToHitLocation();

	ATDMobaPlayerCameraManager* TDMobaCameraManager = nullptr;
	void ZoomIn(float val);


protected:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	

private:
	bool bKeepMovingToMouse = false;
	bool bKeepCameraToPawn = false;
	float ignoreDistance = 100.f;
};
