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

	// ��� �� ��ų ���� ����
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

	// Ÿ�� �� �ʱ�ȭ
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
	// ��Ÿ�� üũ
	if (IsCooldown(InSkillActionType))
		return;

	// ��ų ����� üũ
	if (IsPlayingSkill)
		return;
	
	// ��ų ����
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

	// ��ų �ִϸ��̼� �÷���
	AnimInstance->Montage_Play(Info->SkillAnim, 1.0f);

	// Montage Instance �� ���Ӱ� �����Ǹ鼭 Delegate�� ��ų ���ø��� �Ź� ������ �־�� �Ѵ�.
	AnimInstance->Montage_SetEndDelegate(MontageEndDelegate);

	IsPlayingSkill = true;
}

void URPGSkillComponent::SkillEnd()
{
	// ��ų�� ���� �Ǿ��� �� ��Ÿ���� ����
	StartCooldown(CurrentPlayingAction);

	// ��ų ��� ���� ó��
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