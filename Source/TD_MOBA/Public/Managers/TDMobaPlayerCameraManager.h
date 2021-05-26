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
	/*非锁定下相机左右移动*/
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Val);
	
	/*非锁定下相机上下移动*/
	UFUNCTION(BlueprintCallable)
	void MoveUp(float Val);
	
	/*非锁定下相机远近移动*/
	UFUNCTION(BlueprintCallable)
	void ZoomIn(float Val);

	/*锁定相机在Pawn的原始位置*/
	UFUNCTION(BlueprintCallable)
	void LockCamera(bool Lock);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCameraLocak()
	{
		return bLockCamera;
	}

	/*返回pawn的位置*/
	UFUNCTION(BlueprintCallable)
	void ResetCameraPOV()
	{
		if (!bLockCamera)
			FreeCamOffset = GetPawnCamera()->GetComponentLocation();
	};

	UCameraComponent* GetPawnCamera();

protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	bool bLockCamera = true;
	UCameraComponent* PawnCamera = nullptr;

	float ZoomVal = 0.f;
};
