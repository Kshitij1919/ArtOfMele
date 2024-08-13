// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/GlobalData.h"
#include "Containers/Map.h"
#include "Interfaces/CombatAttacks.h"
#include "ArtOfMeleGameInstance.generated.h"

/**
 * 
 */
class UAnimMontage;

UCLASS()
class ARTOFMELE_API UArtOfMeleGameInstance : public UGameInstance, public ICombatAttacks
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnyWhere, Category = "Combat")
	TMap<FAttackDetails, TObjectPtr<UAnimMontage>> AttackDetailsToAnimationMappings;

public:

	UFUNCTION(BlueprintCallable, Category = "Combat")
	UAnimMontage* GetAttackAnimation(const FAttackDetails& AttackDetail) const;

#pragma region Interface Implementation
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UAnimMontage* GetAttackFromAttackDetail(const FAttackDetails& AttackDetail) const;
	UAnimMontage* GetAttackFromAttackDetail_Implementation(const FAttackDetails& AttackDetail) const override;
#pragma endregion
	
};
