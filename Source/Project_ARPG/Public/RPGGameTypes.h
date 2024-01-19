// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ESkillActionType : uint8 
{
	NormalAttack = 0,
	Dash,
	SkillAction1,
	Max
};
ENUM_RANGE_BY_COUNT(ESkillActionType, ESkillActionType::Max);

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Melee = 0,
	Dash,
	RangeAttack,
};