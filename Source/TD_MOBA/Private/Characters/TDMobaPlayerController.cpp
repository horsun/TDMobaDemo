// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDMobaPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UObject/UObjectGlobals.h"
#include "Blueprint/UserWidget.h"

ATDMobaPlayerController::ATDMobaPlayerController(const FObjectInitializer& ObjectInitializer)
{
	PlayerCameraManagerClass = ATDMobaPlayerCameraManager::StaticClass();
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
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
	InputComponent->BindAxis("ZoomCamera",this,&ATDMobaPlayerController::ZoomIn);
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
	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if ((GetPawn()->GetActorLocation() - hit.Location).Size() >= ignoreDistance)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, hit.Location);
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
}

void ATDMobaPlayerController::BeginPlay()
{
	TDMobaCameraManager = Cast<ATDMobaPlayerCameraManager>(PlayerCameraManager);
	//显示光标，并将光标替换
	bShowMouseCursor = true;
	TSubclassOf<UUserWidget> CursorWidget = LoadClass<UUserWidget>(this, TEXT("/Game/Blueprints/UMG/CursorWidget.CursorWidget_C"));
	if (CursorWidget)
	{
		UUserWidget * CursorWidgetObject = CreateWidget(GetWorld(), CursorWidget);
		SetMouseCursorWidget(EMouseCursor::Default, CursorWidgetObject);
	}
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
	TDMobaCameraManager->ZoomIn(val*20);
}