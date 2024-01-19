// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_ARPG.h"
#include "Components/ActorComponent.h"
#include "RPGSkillComponent.generated.h"

USTRUCT()
struct FRPGSkillInfo
{
	GENERATED_USTRUCT_BODY()

public:
	
	// 일반 공격
	UPROPERTY()
	TArray<UAnimMontage*> NormalAttackAnims;

	TArray<int32> NormalAttackIds;
	int32 CurrentNormalAttackIndex;

	// 스킬
	UPROPERTY()
	UAnimMontage* SkillAnim;

	int32 SkillId;

	// 쿨타임
	float MaxCooldown;
	float CurrentCooldown;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ARPG_API URPGSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URPGSkillComponent();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void UseSkillAction(ESkillActionType InSkillActionType);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SkillAnimEnd(UAnimMontage* Montage, bool bInterrupted);

	// 스킬 Animation Montage 로드
	class UAnimMontage* LoadSkillAnim(int32 InId);

	void SetSkillInfo( ESkillActionType InSkillActionType );
	void SkillProcess();
	void SkillEnd();

	// 쿨타임
	void UpdateCooldown(float InDeltaTime);
	void StartCooldown(ESkillActionType InSkillActionType);
	bool IsCooldown(ESkillActionType InSkillActionType);

protected:
	UPROPERTY()
	class ARPGCharacter* Character;

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UPROPERTY()
	TMap<ESkillActionType, FRPGSkillInfo> SkillInfos;

	ESkillActionType CurrentPlayingAction = ESkillActionType::Max;
	bool IsPlayingSkill = false;

	FOnMontageEnded MontageEndDelegate;
};
