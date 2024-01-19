// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGPlayerController.h"
#include "RPGCharacter.h"
#include "Skill/RPGSkillComponent.h"
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
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnNormalAttackAction);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnDashAction);
		EnhancedInputComponent->BindAction(SkillAction1, ETriggerEvent::Triggered, this, &ARPGPlayerController::OnSkillAction1);
	}
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ARPGCharacter>(GetCharacter());
}

void ARPGPlayerController::OnMoveAction(const FInputActionValue& InValue)
{
	if (PlayerCharacter)
	{
		FVector2D MovementAxis = InValue.Get<FVector2D>();
		PlayerCharacter->Move(MovementAxis);
	}
}

void ARPGPlayerController::OnLookAction(const FInputActionValue& InValue)
{
	if (PlayerCharacter)
	{
		FVector2D LookAxis = InValue.Get<FVector2D>();
		PlayerCharacter->Look(LookAxis);
	}
}

void ARPGPlayerController::OnJumpAction()
{
	if (PlayerCharacter)
		PlayerCharacter->Jump();
}

void ARPGPlayerController::OnJumpEndAction()
{
	if (PlayerCharacter)
		PlayerCharacter->StopJumping();
}

void ARPGPlayerController::OnNormalAttackAction()
{
	if (PlayerCharacter && PlayerCharacter->GetSkillComponent())
		PlayerCharacter->GetSkillComponent()->UseSkillAction(ESkillActionType::NormalAttack);
}

void ARPGPlayerController::OnDashAction()
{
	if (PlayerCharacter && PlayerCharacter->GetSkillComponent())
		PlayerCharacter->GetSkillComponent()->UseSkillAction(ESkillActionType::Dash);
}

void ARPGPlayerController::OnSkillAction1()
{
	if (PlayerCharacter && PlayerCharacter->GetSkillComponent())
		PlayerCharacter->GetSkillComponent()->UseSkillAction(ESkillActionType::SkillAction1);
}