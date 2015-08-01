// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "JustDoIT.h"
#include "JustDoITCharacter.h"
#include "JustDoITProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include <Runtime/Engine/Public/Engine.h>
#include <Runtime/CoreUObject/Public/Templates/Casts.h>

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AJustDoITCharacter

AJustDoITCharacter::AJustDoITCharacter()
{
	InteractionRange = 200.0f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJustDoITCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AJustDoITCharacter::TouchStarted);
	if( EnableTouchscreenMovement(InputComponent) == false )
	{
		InputComponent->BindAction("Fire1", IE_Pressed, this, &AJustDoITCharacter::OnFire1);
		InputComponent->BindAction("Fire2", IE_Pressed, this, &AJustDoITCharacter::OnFire2);
	}
	
	InputComponent->BindAxis("MoveForward", this, &AJustDoITCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AJustDoITCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AJustDoITCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AJustDoITCharacter::LookUpAtRate);
}

void AJustDoITCharacter::OnFire1()
{ 
	if (CurrentInteractableActor)
	{
		if (ToolTypeL == 0 && CurrentInteractableActor->ToolType != 0)
		{
			ToolTypeL = CurrentInteractableActor->ToolType;
		}
		else
		{
			CurrentInteractableActor->OnInteraction(ToolTypeL);
			if (CurrentInteractableActor->ProblemType != 0 || CurrentInteractableActor->ToolType != 0)
				ToolTypeL = 0;
		}
		UpdateLeftTool();
	}
}

void AJustDoITCharacter::OnFire2()
{
	if (CurrentInteractableActor)
	{
		if (ToolTypeR == 0 && CurrentInteractableActor->ToolType != 0)
		{
			ToolTypeR = CurrentInteractableActor->ToolType;
		}
		else
		{
			CurrentInteractableActor->OnInteraction(ToolTypeR);
			if (CurrentInteractableActor->ProblemType != 0 || CurrentInteractableActor->ToolType != 0)
				ToolTypeR = 0;
		}
		UpdateRightTool();
	}
}

void AJustDoITCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if( TouchItem.bIsPressed == true )
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AJustDoITCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if( ( FingerIndex == TouchItem.FingerIndex ) && (TouchItem.bMoved == false) )
	{
		OnFire1();
	}
	TouchItem.bIsPressed = false;
}

void AJustDoITCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && ( TouchItem.FingerIndex==FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D( MoveDelta.X, MoveDelta.Y) / ScreenSize;									
					if (ScaledDelta.X != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (ScaledDelta.Y != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y* BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void AJustDoITCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AJustDoITCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AJustDoITCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJustDoITCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AJustDoITCharacter::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if(FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch )
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AJustDoITCharacter::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &AJustDoITCharacter::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AJustDoITCharacter::TouchUpdate);
	}
	return bResult;
}

void AJustDoITCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Item = Cast<AJustDoITActor>(Raycast(InteractionRange).GetActor());

	if (Item != CurrentInteractableActor)
	{
		if (CurrentInteractableActor)
			CurrentInteractableActor->OnFinishPlayerLookAt();

		CurrentInteractableActor = Item;

		if (CurrentInteractableActor)
			CurrentInteractableActor->OnStartPlayerLookAt();
	}
}

void AJustDoITCharacter::UpdateLeftTool_Implementation()
{
}

void AJustDoITCharacter::UpdateRightTool_Implementation()
{
}


#define COLLISION_TRACE ECC_GameTraceChannel1
FHitResult AJustDoITCharacter::Raycast(float Range)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	const FVector TraceDirection = CameraRotation.Vector();

	FVector StartTrace;
	StartTrace = CameraLocation + TraceDirection * ((GetActorLocation() - CameraLocation) | TraceDirection); // ?

	const FVector EndTrace = StartTrace + TraceDirection * Range;

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName("InteractionTrace"), true, this);
	TraceParams.bTraceAsyncScene = true;

	GetWorld()->LineTraceSingle(HitResult, StartTrace, EndTrace, COLLISION_TRACE, TraceParams);

	return HitResult;
}
