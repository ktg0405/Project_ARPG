// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameDataManager.generated.h"

UENUM()
enum class EGameDataTableType : uint8 
{
	Skill = 0,
	PC
};

/**
 * 
 */
UCLASS()
class PROJECT_ARPG_API URPGGameDataManager : public UObject
{
	GENERATED_BODY()
	
public:
	static URPGGameDataManager* GetInstance();

	void Init();
	
	// Data Get ÇÔ¼ö
	struct FRPGSkillData* GetSkillData(int32 InId);		// Skill Data
	struct FRPGPCData* GetPCData(int32 InId);			// PC Data

private:
	void SetDataTable(EGameDataTableType InDataTableType, const FString& InDataPath);

private:
	static URPGGameDataManager* Instance;

	TMap<EGameDataTableType, class UDataTable*> DataTableMap;
};

#define GAMEDATAMANAGER		URPGGameDataManager::GetInstance()