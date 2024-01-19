// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/RPGGameDataManager.h"
#include "GameData/RPGSkillData.h"
#include "GameData/RPGPCData.h"

URPGGameDataManager* URPGGameDataManager::Instance;

URPGGameDataManager* URPGGameDataManager::GetInstance()
{
	if (!Instance)
		Instance = NewObject<URPGGameDataManager>();

	return Instance;
}

void URPGGameDataManager::Init()
{
	// 데이터 테이블 셋팅
	SetDataTable(EGameDataTableType::Skill,		TEXT("/Game/GameData/SkillData.SkillData"));
	SetDataTable(EGameDataTableType::PC,		TEXT("/Game/GameData/PCData.PCData"));
}

FRPGSkillData* URPGGameDataManager::GetSkillData(int32 InId)
{
	UDataTable* SkillDataTable = DataTableMap.FindRef(EGameDataTableType::Skill);
	if(SkillDataTable)
		return SkillDataTable->FindRow<FRPGSkillData>(*FString::FromInt(InId), TEXT(""));

	return nullptr;
}

FRPGPCData* URPGGameDataManager::GetPCData(int32 InId)
{
	UDataTable* PCDataTable = DataTableMap.FindRef(EGameDataTableType::PC);
	if (PCDataTable)
		return PCDataTable->FindRow<FRPGPCData>(*FString::FromInt(InId), TEXT(""));

	return nullptr;
}

void URPGGameDataManager::SetDataTable(EGameDataTableType InDataTableType, const FString& InDataPath)
{
	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, *InDataPath);
	if (DataTable)
	{
		if (!DataTableMap.Contains(InDataTableType))
			DataTableMap.Emplace(InDataTableType, DataTable);
	}
}