// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/GlobalData.h"
#include "CharacterInterface.generated.h"

#pragma region custom struct return types for functions
//return type for getting Character States
USTRUCT(BlueprintType)
struct FCharacterStates
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadWrite)
	bool bIsInCombat = false;

	UPROPERTY(BlueprintReadWrite)
	ECharacterLocomotionStates LocomotionStates = ECharacterLocomotionStates::WALKING;

	UPROPERTY(BlueprintReadWrite)
	ECombatStates CurrentCombatState = ECombatStates::NEUTRAL;
};

//return type for getting Character States
USTRUCT(BlueprintType)
struct FCharacterValues
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadWrite)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	FVector Acceleration = FVector::ZeroVector;
};
#pragma endregion


// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTOFMELE_API ICharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// for getting current character states
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  Category = "CharacterInterfaces")
	FCharacterStates GetCharacterStates();

	//for getting current character essential values
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  Category = "CharacterInterfaces")
	FCharacterValues GetCharacterEssentialValues();

	//Update Rotation Setting of Character 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterInterfaces")
	void UpdateCharacterRotationSetting(const bool IsCharacterInCombat);

	//Update Character Locomotion states
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterInterfaces")
	void UpdateCharacterLocomotionState(const ECharacterLocomotionStates IncomingLocomotionState);

};
