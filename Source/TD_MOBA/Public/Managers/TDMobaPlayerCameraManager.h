// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
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

protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
