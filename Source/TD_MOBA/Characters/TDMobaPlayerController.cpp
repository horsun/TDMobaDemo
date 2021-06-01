// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMobaPlayerController.h"

#include "MOBACharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UObject/UObjectGlobals.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ATDMobaPlayerController::ATDMobaPlayerController(const FObjectInitializer& ObjectInitializer)
{
	PlayerCameraManagerClass = ATDMobaPlayerCameraManager::StaticClass();
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bShowMouseCursor = true;
}


void ATDMobaPlayerController::SetupInputComponent()
{
	// InputComponent->BindAction("LogCamera_NextEntry", IE_Pressed, this, &AVisualLoggerCameraController::ShowNextEntry);
	Super::SetupInputComponent();
	//Action
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATDMobaPlayerController::SetDestination_Pressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATDMobaPlayerController::SetDestination_Released);
	InputComponent->BindAction("ViewerSwitch", IE_Pressed, this, &ATDMobaPlayerController::ViewerSwitch);
	InputComponent->BindAction("StopAction", IE_Pressed, this, &ATDMobaPlayerController::StopAction);
	InputComponent->BindAction("FindPawn", IE_Pressed, this, &ATDMobaPlayerController::FindPawn_Pressed);
	InputComponent->BindAction("FindPawn", IE_Released, this, &ATDMobaPlayerController::FindPawn_Released);
	//Axis
	InputComponent->BindAxis("ZoomCamera", this, &ATDMobaPlayerController::ZoomIn);
}

void ATDMobaPlayerController::SetDestination_Pressed()
{
	bKeepMovingToMouse = true;
}

void ATDMobaPlayerController::SetDestination_Released()
{
	bKeepMovingToMouse = false;
}

void ATDMobaPlayerController::MoveToHitLocation()
{
	FHitResult hit;
	bool bHit = GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if (bHit && (GetPawn()->GetActorLocation() - hit.Location).Size() >= ignoreDistance)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, hit.Location);
		UMaterial* DecalMat = LoadObject<UMaterial>(nullptr,TEXT("Material'/Game/UI/M_Cursor_Decal.M_Cursor_Decal'"),
		                                            nullptr, LOAD_None, nullptr);
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMat, FVector::OneVector, hit.Location,
		                                       hit.Normal.Rotation(), 2.f);
	}
}

void ATDMobaPlayerController::Tick(float DeltaSeconds)
{
	if (bKeepCameraToPawn)
	{
		TDMobaCameraManager->ResetCameraPOV();
	}
	if (bKeepMovingToMouse)
	{
		MoveToHitLocation();
	}
	// if (!bUIMode)
	// {
	// 	FHitResult hit;
	// 	if (GetHitResultUnderCursor(ECC_Visibility, true, hit))
	// 	{
	// 		AMOBACharacter* hitActor = Cast<AMOBACharacter>(hit.Actor);
	// 		if (hitActor)
	// 		{
	// 			hitActor->test();
	// 		}
	// 	}
	// }
}

void ATDMobaPlayerController::BeginPlay()
{
	TDMobaCameraManager = Cast<ATDMobaPlayerCameraManager>(PlayerCameraManager);
	//显示光标，并将光标替换
	// TSubclassOf<UUserWidget> CursorWidget = LoadClass<UUserWidget>(this, TEXT("/Game/Blueprints/UMG/CursorWidget.CursorWidget_C"));
	// if (CursorWidget)
	// {
	// 	UUserWidget * CursorWidgetObject = CreateWidget(GetWorld(), CursorWidget);
	// 	SetMouseCursorWidget(EMouseCursor::Default, CursorWidgetObject);
	// }
}

void ATDMobaPlayerController::ViewerSwitch()
{
	if (TDMobaCameraManager)
	{
		TDMobaCameraManager->LockCamera(!TDMobaCameraManager->IsCameraLocak());
	}
}

void ATDMobaPlayerController::StopAction()
{
	StopMovement();
}

void ATDMobaPlayerController::FindPawn_Pressed()
{
	bKeepCameraToPawn = true;
}

void ATDMobaPlayerController::FindPawn_Released()
{
	bKeepCameraToPawn = false;
}

void ATDMobaPlayerController::ZoomIn(float val)
{
	TDMobaCameraManager->ZoomIn(val * 20);
}
