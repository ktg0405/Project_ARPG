// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGPlayerController.h"
#include "RPGCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

	// Input Action ¹ÙÀÎµù
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) 
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnMoveAction);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARPGPlayerController::OnJumpAction);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARPGPlayerController::OnJumpEndAction);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnLookAction);
	}
}

void ARPGPlayerController::OnMoveAction(const FInputActionValue& InValue)
{
	ARPGCharacter* PlayerCharacter = Cast<ARPGCharacter>(GetCharacter());
	if (PlayerCharacter)
	{
		FVector2D MovementAxis = InValue.Get<FVector2D>();
		PlayerCharacter->Move(MovementAxis);
	}
}

void ARPGPlayerController::OnLookAction(const FInputActionValue& InValue)
{
	ARPGCharacter* PlayerCharacter = Cast<ARPGCharacter>(GetCharacter());
	if (PlayerCharacter)
	{
		FVector2D LookAxis = InValue.Get<FVector2D>();
		PlayerCharacter->Look(LookAxis);
	}
}

void ARPGPlayerController::OnJumpAction()
{
	if (GetCharacter())
		GetCharacter()->Jump();
}

void ARPGPlayerController::OnJumpEndAction()
{
	if (GetCharacter())
		GetCharacter()->StopJumping();
}

