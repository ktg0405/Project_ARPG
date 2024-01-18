// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ESkillActionType : uint8 
{
	NormalAttack = 0,
	SkillAction1,
	Dash
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Melee = 0,
	Dash
};