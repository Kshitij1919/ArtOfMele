// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CharacterInterface.h" // interface Include
#include "BaseCharacter.generated.h"

enum class ECharacterLocomotionStates : uint8;

UCLASS()
class ARTOFMELE_API ABaseCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

private:
#pragma region Character Essential Values

	//Velocity values
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "EssentailValues")
	FVector PreviousVelocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "EssentailValues")
	FVector Acceleration = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "EssentailValues")
	float Speed = 0.0f;
#pragma endregion



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Locomotion Variables*/
	UPROPERTY(BlueprintReadWrite, category = "CharacterStates")
	ECharacterLocomotionStates LocomotionStates;

#pragma region Essentail values function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EssentailValues")
	FVector CalculateAcceleration() const;
	virtual FVector CalculateAcceleration_Implementation() const;

	
#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Character Interface Implementation
	FCharacterValues GetCharacterEssentialValues();
	virtual FCharacterValues GetCharacterEssentialValues_Implementation() override;

	FCharacterStates GetCharacterStates();
	virtual FCharacterStates GetCharacterStates_Implementation() override;

	void UpdateCharacterRotationSetting(const bool IsCharacterInCombat);
	virtual void UpdateCharacterRotationSetting_Implementation(const bool IsCharacterInCombat) override;
	
#pragma endregion



};
