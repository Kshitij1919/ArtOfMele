// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatAttacks.generated.h"

struct FAttackDetails;
//class UAnimMontage;

// This class does not need to be modified.
UINTERFACE(MinimalAPI/*, BlueprintType*/)
class UCombatAttacks : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */


class ARTOFMELE_API ICombatAttacks
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UAnimMontage* GetAttackFromAttackDetail(const FAttackDetails& AttackDetail) const;
};
