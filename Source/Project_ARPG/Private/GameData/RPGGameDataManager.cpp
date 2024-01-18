// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/RPGGameDataManager.h"
#include "GameData/RPGSkillData.h"

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
	SetDataTable(EGameDataTableType::Skill, TEXT("/Game/GameData/SkillData.SkillData"));
}

FRPGSkillData* URPGGameDataManager::GetSkillData(int32 InId)
{
	UDataTable* SkillDataTable = DataTableMap.FindRef(EGameDataTableType::Skill);
	if(SkillDataTable)
		return SkillDataTable->FindRow<FRPGSkillData>(*FString::FromInt(InId), TEXT(""));

	return nullptr;
}

void URPGGameDataManager::SetDataTable(EGameDataTableType InDataTableType, const FString& InDataPath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*InDataPath);
	if (DataTable.Succeeded())
	{
		if (!DataTableMap.Contains(InDataTableType))
			DataTableMap.Emplace(InDataTableType, DataTable.Object);
	}
}