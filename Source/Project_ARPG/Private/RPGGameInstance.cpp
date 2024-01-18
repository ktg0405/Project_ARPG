// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"
#include "GameData/RPGGameDataManager.h"

URPGGameInstance::URPGGameInstance()
{
	if (URPGGameDataManager* GameDataManager = URPGGameDataManager::GetInstance())
		GameDataManager->Init();
}