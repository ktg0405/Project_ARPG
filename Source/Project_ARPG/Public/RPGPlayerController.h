// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_ARPG.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ARPG_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnMoveAction(const struct FInputActionValue& InValue);
	void OnLookAction(const struct FInputActionValue& InValue);
	void OnJumpAction();
	void OnJumpEndAction();
	void OnNormalAttackAction();
	void OnDashAction();
	void OnSkillAction1();

protected:

	// InputAction ฐüทร
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* NormalAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction1;

	UPROPERTY()
	class ARPGCharacter* PlayerCharacter;
};
