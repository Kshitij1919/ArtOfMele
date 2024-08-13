// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ArtOfMeleGameInstance.h"

UAnimMontage* UArtOfMeleGameInstance::GetAttackAnimation(const FAttackDetails& AttackDetail) const
{
	return /*TObjectPtr<UAnimMontage>* MontageToPlay =*/ *(AttackDetailsToAnimationMappings.Find(AttackDetail));
	 
}

UAnimMontage* UArtOfMeleGameInstance::GetAttackFromAttackDetail_Implementation(const FAttackDetails& AttackDetail) const
{
	return *(AttackDetailsToAnimationMappings.Find(AttackDetail));
	//return	AttackDetailsToAnimationMappings.Find(AttackDetail);
}
