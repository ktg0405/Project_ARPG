// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/RPGSkillComponent.h"
#include "GameData/RPGGameDataManager.h"
#include "GameData/RPGPCData.h"
#include "GameData/RPGSkillData.h"
#include "RPGCharacter.h"

URPGSkillComponent::URPGSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URPGSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ARPGCharacter>(GetOwner());
	if (Character)
		AnimInstance = Cast<UAnimInstance>(Character->GetMesh()->GetAnimInstance());

	// Delegate Binding
	MontageEndDelegate.BindUObject(this, &URPGSkillComponent::SkillAnimEnd);

	// 사용 할 스킬 정보 셋팅
	for (ESkillActionType Type : TEnumRange<ESkillActionType>())
	{
		if(Type != ESkillActionType::Max)
			SetSkillInfo(Type);
	}
}

void URPGSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateCooldown(DeltaTime);
}

void URPGSkillComponent::SetSkillInfo(ESkillActionType InSkillActionType)
{
	FRPGPCData* PCData = GAMEDATAMANAGER->GetPCData(1);
	if (!PCData)
		return;

	FRPGSkillData* SkillData;
	FRPGSkillInfo SkillInfo;
	int32 SkillId = 0;

	// 타입 별 초기화
	switch (InSkillActionType)
	{
	case ESkillActionType::NormalAttack:
	{
		SkillId = PCData->NormalAttack1_ID;
		SkillInfo.NormalAttackIds.Add(PCData->NormalAttack1_ID);
		SkillInfo.NormalAttackIds.Add(PCData->NormalAttack2_ID);
		SkillInfo.NormalAttackIds.Add(PCData->NormalAttack3_ID);
		SkillInfo.CurrentNormalAttackIndex = 0;

		SkillInfo.NormalAttackAnims.Empty();
		for (int32 Id : SkillInfo.NormalAttackIds)
			SkillInfo.NormalAttackAnims.Emplace(LoadSkillAnim(Id));

		SkillInfo.SkillAnim = LoadSkillAnim(SkillId);
	}
	break;

	case ESkillActionType::Dash:
	{
		SkillId = PCData->Dash_ID;
		SkillInfo.SkillAnim = LoadSkillAnim(SkillId);
	}
	break;

	case ESkillActionType::SkillAction1:
	{
		SkillId = PCData->SkillAction1_ID;
		SkillInfo.SkillAnim = LoadSkillAnim(SkillId);
	}
	break;
	}

	SkillInfo.SkillId = SkillId;
	SkillData = GAMEDATAMANAGER->GetSkillData(SkillId);
	SkillInfo.MaxCooldown = SkillData ? static_cast<float>(SkillData->Cooldown) : 0.0f;
	SkillInfo.CurrentCooldown = 0.0f;

	if (!SkillInfos.Contains(InSkillActionType))
		SkillInfos.Emplace(InSkillActionType, SkillInfo);
}

void URPGSkillComponent::UseSkillAction(ESkillActionType InSkillActionType)
{
	// 쿨타임 체크
	if (IsCooldown(InSkillActionType))
		return;

	// 스킬 사용중 체크
	if (IsPlayingSkill)
		return;
	
	// 스킬 실행
	CurrentPlayingAction = InSkillActionType;
	SkillProcess();
}

void URPGSkillComponent::SkillProcess()
{
	FRPGSkillInfo* Info = SkillInfos.Find(CurrentPlayingAction);
	if (!Info)
		return;

	if (!AnimInstance)
		return;

	// 스킬 애니메이션 플레이
	AnimInstance->Montage_Play(Info->SkillAnim, 1.0f);

	// Montage Instance 가 새롭게 생성되면서 Delegate를 스킬 사용시마다 매번 셋팅해 주어야 한다.
	AnimInstance->Montage_SetEndDelegate(MontageEndDelegate);

	IsPlayingSkill = true;
}

void URPGSkillComponent::SkillEnd()
{
	// 스킬이 종료 되었을 때 쿨타임을 적용
	StartCooldown(CurrentPlayingAction);

	// 스킬 사용 종료 처리
	IsPlayingSkill = false;
	CurrentPlayingAction = ESkillActionType::Max;
}

void URPGSkillComponent::SkillAnimEnd(UAnimMontage* Montage, bool bInterrupted)
{
	SkillEnd();
}

void URPGSkillComponent::UpdateCooldown(float InDeltaTime)
{
	for (ESkillActionType Type : TEnumRange<ESkillActionType>())
	{
		if (FRPGSkillInfo* Info = SkillInfos.Find(Type))
			Info->CurrentCooldown = FMath::Max(0.0f, Info->CurrentCooldown - InDeltaTime);
	}
}

void URPGSkillComponent::StartCooldown(ESkillActionType InSkillActionType)
{
	if (FRPGSkillInfo* Info = SkillInfos.Find(InSkillActionType))
		Info->CurrentCooldown = Info->MaxCooldown;
}

bool URPGSkillComponent::IsCooldown(ESkillActionType InSkillActionType)
{
	if (FRPGSkillInfo* Info = SkillInfos.Find(InSkillActionType))
		return Info->CurrentCooldown > 0;
	
	return false;
}

UAnimMontage* URPGSkillComponent::LoadSkillAnim(int32 InId)
{
	FRPGSkillData* SkillData = GAMEDATAMANAGER->GetSkillData(InId);
	if(SkillData)
		return LoadObject<UAnimMontage>(nullptr, *SkillData->SkillAnimPath);

	return nullptr;
}