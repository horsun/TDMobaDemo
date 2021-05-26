// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TDMobaPlayerCameraManager.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

/*相关内容可以参照jerish博客内容：https://blog.csdn.net/u012999985/article/details/68947410*/

//
// void UStrategyCameraComponent::UpdateCameraMovement( const APlayerController* InPlayerController )
// {
// 	// No mouse support on mobile
// #if PLATFORM_DESKTOP
// 	ULocalPlayer* const LocalPlayer =  Cast<ULocalPlayer>(InPlayerController->Player);
// 	if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->Viewport )
// 	{
// 		FVector2D MousePosition;
// 		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition) == false)
// 		{
// 			return;
// 		}
//
// 		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
// 		const float ScrollSpeed = 60.0f;
// 		const FIntPoint ViewportSize = Viewport->GetSizeXY();
// 		const uint32 ViewLeft = FMath::TruncToInt(LocalPlayer->Origin.X * ViewportSize.X);
// 		const uint32 ViewRight = ViewLeft + FMath::TruncToInt(LocalPlayer->Size.X * ViewportSize.X);
// 		const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
// 		const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);
// 		
// 		const float MaxSpeed = CameraScrollSpeed * FMath::Clamp(ZoomAlpha, 0.3f, 1.0f);
//
// 		AStrategyGameState const* const MyGameState = GetWorld()->GetGameState<AStrategyGameState>();
// 		bool bNoScrollZone = false;
// 		FVector MouseCoords( MousePosition, 0.0f );
// 		for (int iZone = 0; iZone < NoScrollZones.Num() ; iZone++)
// 		{
// 			FBox EachZone = NoScrollZones[ iZone ];
// 			if( EachZone.IsInsideXY( MouseCoords ) == true )
// 			{
// 				bNoScrollZone = true;
// 			}
// 		}
//
// 		const uint32 MouseX = MousePosition.X;
// 		const uint32 MouseY = MousePosition.Y;
// 		float SpectatorCameraSpeed = MaxSpeed;
// 		ASpectatorPawn* SpectatorPawn = NULL;
// 		if( GetPlayerController() != NULL )
// 		{
// 			SpectatorPawn = GetPlayerController()->GetSpectatorPawn();
// 			if( SpectatorPawn->GetMovementComponent() != NULL )
// 			{
// 				SpectatorCameraSpeed = GetDefault<UStrategySpectatorPawnMovement>(SpectatorPawn->GetMovementComponent()->GetClass())->MaxSpeed;
// 			}
// 		}
// 		if (!bNoScrollZone)
// 		{
// 			if (MouseX >= ViewLeft && MouseX <= (ViewLeft + CameraActiveBorder))
// 			{
// 				const float delta = 1.0f - float(MouseX - ViewLeft) / CameraActiveBorder;
// 				SpectatorCameraSpeed = delta * MaxSpeed;
// 				MoveRight(-ScrollSpeed * delta);
// 			}
// 			else if (MouseX >= (ViewRight - CameraActiveBorder) && MouseX <= ViewRight)
// 			{
// 				const float delta = float(MouseX - ViewRight + CameraActiveBorder) / CameraActiveBorder;
// 				SpectatorCameraSpeed = delta * MaxSpeed;
// 				MoveRight(ScrollSpeed * delta);
// 			}
//
// 			if (MouseY >= ViewTop && MouseY <= (ViewTop + CameraActiveBorder))
// 			{
// 				const float delta = 1.0f - float(MouseY - ViewTop) / CameraActiveBorder;
// 				SpectatorCameraSpeed = delta * MaxSpeed;
// 				MoveForward(ScrollSpeed * delta);
// 			}
// 			else if (MouseY >= (ViewBottom - CameraActiveBorder) && MouseY <= ViewBottom)
// 			{
// 				const float delta = float(MouseY - (ViewBottom - CameraActiveBorder)) / CameraActiveBorder;
// 				SpectatorCameraSpeed = delta * MaxSpeed;
// 				MoveForward(-ScrollSpeed * delta);
// 			}
//
// 			if( SpectatorPawn != NULL )
// 			{
// 				UFloatingPawnMovement* PawnMovementComponent = Cast<UFloatingPawnMovement>(SpectatorPawn->GetMovementComponent());
// 				if (PawnMovementComponent)
// 				{
// 					PawnMovementComponent->MaxSpeed = SpectatorCameraSpeed;
// 				}
// 			}
// 		}
// 	}
// #endif
// 	NoScrollZones.Empty();
// }

void ATDMobaPlayerCameraManager::MoveUp(float Val)
{
	FreeCamOffset.X += Val;
}

void ATDMobaPlayerCameraManager::ZoomIn(float Val)
{
	ZoomVal +=Val;
}

void ATDMobaPlayerCameraManager::MoveRight(float Val)
{
	FreeCamOffset.Y += Val;
}

void ATDMobaPlayerCameraManager::LockCamera(bool Lock)
{
	bLockCamera = Lock;
	FreeCamOffset = bLockCamera ? FVector::ZeroVector : GetPawnCamera()->GetComponentLocation();
}

UCameraComponent* ATDMobaPlayerCameraManager::GetPawnCamera()
{
	if (!PawnCamera)
	{
		PawnCamera = Cast<UCameraComponent>(PCOwner->GetPawn()->GetComponentByClass(UCameraComponent::StaticClass()));
	}
	return PawnCamera;
}

void ATDMobaPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	/**
	 *AActor::CalcCamera()貌似也能实现这个功能 对camera进行offset
	 */

	if ((PendingViewTarget.Target != NULL) && BlendParams.bLockOutgoing && OutVT.Equal(ViewTarget))
	{
		return;
	}

	FMinimalViewInfo OrigPOV = OutVT.POV;

	OutVT.POV.FOV = DefaultFOV;
	OutVT.POV.OrthoWidth = DefaultOrthoWidth;
	OutVT.POV.AspectRatio = DefaultAspectRatio;
	OutVT.POV.bConstrainAspectRatio = bDefaultConstrainAspectRatio;
	OutVT.POV.bUseFieldOfViewForLOD = true;
	OutVT.POV.ProjectionMode = bIsOrthographic
		                           ? ECameraProjectionMode::Orthographic
		                           : ECameraProjectionMode::Perspective;
	OutVT.POV.PostProcessSettings.SetBaseValues();
	OutVT.POV.PostProcessBlendWeight = 1.0f;

	UpdateViewTargetInternal(OutVT, DeltaTime);
	/*
	*锁住camera是指相机跟着pawn位移，反之跟着mouse走
	*/
	if (!bLockCamera && GetPawnCamera())
	{
		OutVT.POV.Location = FreeCamOffset;
	}
	FVector zoomVector =OutVT.POV.Rotation.Vector();
	zoomVector.Normalize();
	OutVT.POV.Location +=zoomVector*ZoomVal;

	ApplyCameraModifiers(DeltaTime, OutVT.POV);

	SetActorLocationAndRotation(OutVT.POV.Location, OutVT.POV.Rotation, false);
	UpdateCameraLensEffects(OutVT);
}
