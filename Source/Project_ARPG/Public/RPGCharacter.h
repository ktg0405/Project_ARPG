// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS()
class PROJECT_ARPG_API ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGCharacter();

public:
	virtual void Tick(float DeltaTime) override;

	// 조작 관련 
	void Move(const FVector2D& InAxis);
	void Look(const FVector2D& InAxis);

	class URPGSkillComponent* GetSkillComponent() { return SkillComponent; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class URPGSkillComponent* SkillComponent;
};
