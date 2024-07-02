// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GlobalData.h"
#include "Containers/Map.h"
#include "Containers/Array.h"
#include "Animation/AnimMontage.h"
#include "BaseCombatComponent.generated.h"

class USkeletalMeshComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, Abstract)
class ARTOFMELE_API UBaseCombatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
					/*Variables*/
#pragma region Varaibles for custom Animation montage sequence
	//Current Attack Index for fecthing montage to play from array
	int CurrentAttackIndex = 0;

	//Delegate to bind function after montage complition(Inturrupted/Successfull)
	FOnMontageEnded MontageEndedDelegate;

	//Varaible to store Attack detail for function recurrsion
	TArray<FAttackDetails> AttackSummary;

	//Varaible to store Skeletal Mesh component for function recurrsion
	const USkeletalMeshComponent* SkeletalMeshComp;
#pragma endregion

#pragma region Core Variables
	UPROPERTY(BlueprintGetter = GetIsInCombat, Category = "Combat|CoreVariables")
	bool bIsInCombat = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Combat|CoreVariables")
	uint8 ComboCounter = 0;

	UPROPERTY(BlueprintGetter = GetCombatState, meta = (AllowPrivateAccess = "true"), Category = "Combat|CoreVariables")
	ECombatStates CombatState = ECombatStates::NEUTRAL;

	UPROPERTY(BlueprintGetter = GetIsCharacterDodging, meta = (AllowPrivateAccess = "true"), Category = "Combat|CoreVariables")
	bool bIsCharacterdodging = false;

	UPROPERTY(BlueprintGetter = GetIsCharacterBlocking, meta = (AllowPrivateAccess = "true"), Category = "Combat|CoreVariables")
	bool bIsCharacterBlocking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), category = "Combat|CoreVariables")
	TMap<FAttackDetails, UAnimMontage*> AttackMappings;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), category = "Combat|CoreVariables")
	bool bCanPlayAnimMontage = true;

	UPROPERTY(BlueprintGetter = GetBlockHealth, BlueprintSetter = UpdateBlockHealth, meta = (ClampMin = 0.0f, ClampMax = 100.0f, AllowPrivateAccess = "true"), category = "Combat|CoreVariables")
	float  BlockHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), category = "Combat|CoreVariables")
	TMap<EAttackTarget, UAnimMontage*> SpecialAttackMappings;

	//Variable Modifiers
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 1.0f, AllowPrivateAccess = "true"), category = "Combat|CoreVariables")
	float BlockHealthDamageModifier = 1.0f;

#pragma endregion

public:	
	// Sets default values for this component's properties
	UBaseCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Delegate Binder for Animation Montage Complition(Interuppted/Successfull)
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//Functions
#pragma region Getter Functions
	UFUNCTION(BlueprintGetter)
	bool GetIsInCombat() const;

	UFUNCTION(BlueprintGetter)
	ECombatStates GetCombatState() const;

	UFUNCTION(BlueprintGetter)
	bool GetIsCharacterDodging() const;

	UFUNCTION(BlueprintGetter)
	bool GetIsCharacterBlocking() const;

	UFUNCTION(BlueprintGetter)
	bool CanPlayMontage() const;

	UFUNCTION(BlueprintGetter)
	float GetBlockHealth() const;
#pragma endregion

#pragma region Update States Function
	UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "StateUpdates")
	void UpdateIsCharacterInCombat(const bool bShouldCharacterbeInCombat);
	virtual void UpdateIsCharacterInCombat_Implementation(const bool bShouldCharacterbeInCombat);

	UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "StateUpdates")
	void UpdateCharacterCombatStates(const ECombatStates NewCombatState);
	virtual void UpdateCharacterCombatStates_Implementation(const ECombatStates NewCombatState);

	UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "StateUpdates")
	void UpdateIsCharacterDodging(const bool Dodging);
	virtual void UpdateIsCharacterDodging_Implementation(const bool Dodging);

	UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "StateUpdates")
	void UpdateCanPlayMontage(const bool canplaymontage);
	virtual void UpdateCanPlayMontage_Implementation(const bool canplaymontage);

	UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "StateUpdates")
	void UpdateIsCharacterBlocking(const bool Blocking);
	virtual void UpdateIsCharacterBlocking_Implementation(const bool Blocking);

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "this Function handles both reducing and increasing BlockHealth. Pass the sign along with value (+ for increase, - for Decrease)"), Category = "StatteUpdates")
	void UpdateBlockHealth(const float ChangeInBlockHealth = 0.0f);
#pragma endregion

#pragma region Combat Comp Functions
	UFUNCTION(BlueprintCallable, Category = "CombatFunctions")
	void PerfromAttackSequence(const TArray<FAttackDetails>& AttackDetails, const USkeletalMeshComponent* MeshComp);
#pragma endregion
		
};
