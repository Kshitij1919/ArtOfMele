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

UENUM(BlueprintType, meta = (ToolTip = "This Enum is used for animation notfiy Logic Use only. Do not use this in any other Context"))
enum class ESimplifiedAttackType : uint8
{
	LEFTPUNCH  UMETA(DisplayName = "Left Punch"),
	RIGHTPUNCH UMETA(DisplayName = "Right Punch"),
	LEFTKICK   UMETA(DisplayName = "Left Kick"),
	RIGHTKICK  UMETA(DisplayName = "Right Kick")
};

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

// for mapping Attack Details
USTRUCT(BlueprintType)
struct FAttackDetails : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAttackTarget AttackTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAttackDirection AttackDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
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

	
	FName GetAttackDetailAsFName() const
	{
		FString S_AttackDetail = AttackTargetToString() + AttackDirectionToString() + AttackTargetToString();
		return FName(*S_AttackDetail);
	}

#pragma region Enum to FString Conversions
	// Enum to String Conversions
	 FString AttackTargetToString() const
	{
		switch (AttackTarget)
		{
		case EAttackTarget::HEAD:
			return "Head";
		case EAttackTarget::BODY:
			return "Body";
		default:
			return "Invalid";
		}
	}

	 FString AttackDirectionToString() const
	 {
		 switch (AttackDirection)
		 {
		 case EAttackDirection::LEFT:
			 return "Left";
		 case EAttackDirection::RIGHT:
			 return "Right";
		 default:
			 return "Invalid";
		 }
	 }

	 FString AttackTypeToString() const
	 {
		 switch (AttackType)
		 {
		 case EAttackType::JAB:
			 return "Jab";
		 case EAttackType::CROSS:
			 return "Cross";
		 case EAttackType::HOOK:
			 return "Hook";
		 case EAttackType::FRONTKICK:
			 return "FrontKick";
		 case EAttackType::ROUNDHOUSEKICK:
			 return "RoundHouseKick";
		 default:
			 return "Invalid";
		 }
	 }

#pragma endregion

};

// for creating Custom TMap
#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FAttackDetails& MyStruct);
#else
FORCEINLINE uint32 GetTypeHash(const FAttackDetails& MyStruct)
{
	uint32 Hash = FCrc::MemCrc32(&MyStruct, sizeof(FAttackDetails));
	return Hash;
}
#endif

