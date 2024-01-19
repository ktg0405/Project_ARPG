// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAnimInstance.h"

void URPGAnimInstance::PlayIdle()
{
	if (Montage_IsPlaying(IdleAnim))
		Montage_Play(IdleAnim, 1.0f);
}

void URPGAnimInstance::PlayDeath()
{
	if (Montage_IsPlaying(DeathAnim))
		Montage_Play(DeathAnim, 1.0f);
}