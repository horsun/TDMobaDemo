// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMobaPlayerCameraManager.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

//相关内容可以参照jerish博客内容：https://blog.csdn.net/u012999985/article/details/68947410*/
//关于视野的前后左右移动 是参考了官方的 塔防demo写的，挺好用的，名字叫StrategyGame，可以商城免费下载

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

void ATDMobaPlayerCameraManager::UpdatePOV(FTViewTarget & OutVT)
{
	//锁住camera是指相机跟着pawn位移，反之跟着鼠标走
	if (!bLockCamera && GetPawnCamera())
	{
		//初始化POV
		OutVT.POV.Location = FreeCamOffset;

		FVector2D MousePosition;
		ULocalPlayer* const LocalPlayer = Cast<ULocalPlayer>(PCOwner->Player);
		if (!LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			return;
		}
		FViewport * Viewport = LocalPlayer->ViewportClient->Viewport;
		const FIntPoint ViewportSize = Viewport->GetSizeXY();
		const uint32 ViewLeft = FMath::TruncToInt(LocalPlayer->Origin.X * ViewportSize.X);
		const uint32 ViewRight = ViewLeft + FMath::TruncToInt(LocalPlayer->Size.X * ViewportSize.X);
		const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
		const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);
		const uint32 MouseX = MousePosition.X;//鼠标的x轴
		const uint32 MouseY = MousePosition.Y;//鼠标y轴
		
		//border 参数用于配置 鼠标与最近边的宽度为多少时触发 视点的上下左右偏移
		const uint32 CameraActiveBorder = 20;
		const float ScrollSpeed = 30.f;

		//通过鼠标的位置 判定鼠标在哪条最近的边上
		//delta则是用于对速度有一个非线性的变化
		if (MouseX >= ViewLeft && MouseX <= (ViewLeft + CameraActiveBorder))
		{
			const float delta = 1.0f - float(MouseX - ViewLeft) / CameraActiveBorder;
			MoveRight(-ScrollSpeed * delta);
		}
		else if (MouseX >= (ViewRight - CameraActiveBorder) && MouseX <= ViewRight)
		{
			const float delta = float(MouseX - ViewRight + CameraActiveBorder) / CameraActiveBorder;
			MoveRight(ScrollSpeed * delta);
		}

		if (MouseY >= ViewTop && MouseY <= (ViewTop + CameraActiveBorder))
		{
			const float delta = 1.0f - float(MouseY - ViewTop) / CameraActiveBorder;
			MoveUp(ScrollSpeed * delta);
		}
		else if (MouseY >= (ViewBottom - CameraActiveBorder) && MouseY <= ViewBottom)
		{
			const float delta = float(MouseY - (ViewBottom - CameraActiveBorder)) / CameraActiveBorder;
			MoveUp(-ScrollSpeed * delta);
		}
	}

	//计算ZoomIn /ZoomOut,根据相机的朝向进行距离的拉近拉远。
	FVector zoomVector = OutVT.POV.Rotation.Vector();
	zoomVector.Normalize();
	OutVT.POV.Location += zoomVector * ZoomVal;
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
	UpdatePOV(OutVT);
	

	ApplyCameraModifiers(DeltaTime, OutVT.POV);

	SetActorLocationAndRotation(OutVT.POV.Location, OutVT.POV.Rotation, false);
	UpdateCameraLensEffects(OutVT);
}
