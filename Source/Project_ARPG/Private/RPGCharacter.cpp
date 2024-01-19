// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacter.h"
#include "RPGGameTypes.h"
#include "GameData/RPGSkillData.h"
#include "Skill/RPGSkillComponent.h"

ARPGCharacter::ARPGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	SkillComponent = NewObject<URPGSkillComponent>(this, URPGSkillComponent::StaticClass(), TEXT("SkillComponent"));
	SkillComponent->RegisterComponent();
}

void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARPGCharacter::Move(const FVector2D& InAxis)
{
	if (!Controller)
		return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InAxis.Y);
	AddMovementInput(RightDirection, InAxis.X);
}

void ARPGCharacter::Look(const FVector2D& InAxis)
{
	if (!Controller)
		return;
	
	AddControllerYawInput(InAxis.X);
	AddControllerPitchInput(InAxis.Y);
	
}
