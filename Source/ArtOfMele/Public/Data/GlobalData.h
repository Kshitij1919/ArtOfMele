// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalData.generated.h"

#pragma region Character Locomotion Enums
UENUM(BlueprintType)
enum class ECharacterLocomotionStates : uint8
{
	WALKING UMETA(DisplayName = "Walking"),
	JOGGING UMETA(DisplayName = "Jogging"),
	RUNNING UMETA(DisplayName = "Running"),
};
#pragma endregion

#pragma region Combat Enums

UENUM(BlueprintType)
enum class ECombatStates : uint8
{
	NEUTRAL   UMETA(DisplayName = "Neutral"),
	ATTACKING UMETA(DisplayName = "Attacking"),
	BLOCKING  UMETA(DisplayName = "Blocking"),
	DODGING   UMETA(DisplayName = "Dodging"),

};

UENUM(BlueprintType)
enum class EAttackTarget : uint8
{
	HEAD UMETA(DisplayName = "Head"),
	BODY UMETA(DisplayName = "Body")
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	JAB			   UMETA(DisplayName = "jab"),
	CROSS		   UMETA(DisplayName = "Cross"),
	HOOK           UMETA(DisplayName = "Hook"), 
	FRONTKICK	   UMETA(DisplayName = "Front Kick"),
	ROUNDHOUSEKICK UMETA(DisplayName = "Round House Kick")
};

UENUM(BlueprintType)
enum class EAttackDirection : uint8
{
	LEFT  UMETA(DisplayName = "left"),
	RIGHT UMETA(DisplayName = "Right")
};

#pragma endregion

USTRUCT(BlueprintType)
struct FAttackDetails
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAttackTarget AttackTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAttackDirection AttackDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAttackType AttackType;

	
	FAttackDetails()
		: FAttackDetails(EAttackTarget::HEAD, EAttackDirection::LEFT, EAttackType::JAB)
	{}

	FAttackDetails(EAttackTarget attacktarget, EAttackDirection attackdirection, EAttackType attacktype)
		:AttackTarget(attacktarget), AttackDirection(attackdirection), AttackType(attacktype)
	{}

	FAttackDetails(const FAttackDetails& Other)
		: FAttackDetails(Other.AttackTarget, Other.AttackDirection, Other.AttackType)
	{}

	bool operator==(const FAttackDetails& Other) const
	{
		if (
				AttackTarget == Other.AttackTarget &&
				AttackDirection == Other.AttackDirection &&
				AttackType == Other.AttackType
			)
		{
			return true;
		}

		return false;
	}

};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FAttackDetails& MyStruct);
#else
FORCEINLINE uint32 GetTypeHash(const FAttackDetails& MyStruct)
{
	uint32 Hash = FCrc::MemCrc32(&MyStruct, sizeof(FAttackDetails));
	return Hash;
}
#endif

