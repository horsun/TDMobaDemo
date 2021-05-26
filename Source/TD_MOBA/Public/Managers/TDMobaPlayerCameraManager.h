// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "camera/CameraComponent.h"
#include "TDMobaPlayerCameraManager.generated.h"

/**
 *
 */

UCLASS()
class TD_MOBA_API ATDMobaPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Val);

	UFUNCTION(BlueprintCallable)
		void MoveUp(float Val);

	UFUNCTION(BlueprintCallable)
		void LockCamera(bool Lock);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsCameraLocak()
	{
		return bLockCamera;
	}

	UFUNCTION(BlueprintCallable)
		void ResetCameraPOV()
	{
		if(!bLockCamera)
		FreeCamOffset = GetPawnCamera()->GetComponentLocation();
	};

	UCameraComponent * GetPawnCamera();
	UCameraComponent *PawnCamera = nullptr;

protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	bool bLockCamera = true;
};
