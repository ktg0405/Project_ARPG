// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ARPG_API URPGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void PlayIdle();
	void PlayDeath();
	
protected:
	UPROPERTY(EditAnywhere, Category = Anim)
	UAnimMontage* IdleAnim;
	UPROPERTY(EditAnywhere, Category = Anim)
	UAnimMontage* DeathAnim;
};
