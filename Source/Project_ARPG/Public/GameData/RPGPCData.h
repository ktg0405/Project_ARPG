// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RPGPCData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRPGPCData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NormalAttack1_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NormalAttack2_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NormalAttack3_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Dash_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillAction1_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ResourcePath;
};