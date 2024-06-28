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
	FTimerHandle TimerHandle;
	TObjectPtr<UWorld> World;
	int CurrentAttackIndex = 0;
	FOnMontageEnded MontageEndedDelegate;

	TArray<FAttackDetails> AttackSummary;
	 const USkeletalMeshComponent* SkeletalMeshComp;


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


public:
//Variables



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
#pragma endregion

#pragma region Combat Comp Functions
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (WorldContext = "WorldContext"/*, BlueprintInternalUseOnly = "true"*/), Category = "CombatFunctions")
	void PerfromAttack(UObject* WorldContext,  const TArray<FAttackDetails>& AttackDetail, const USkeletalMeshComponent* MeshComp);
	virtual void PerfromAttack_Implementation(UObject* WorldContext, const TArray<FAttackDetails>& AttackDetail, const USkeletalMeshComponent* MeshComp);

	UFUNCTION(BlueprintCallable, Category = "CombatFunctions")
	void TempAttackSequencer(const TArray<FAttackDetails>& AttackDetails, const USkeletalMeshComponent* MeshComp);
#pragma endregion




public:	
	// Sets default values for this component's properties
	UBaseCombatComponent();

	//Temprory Function delete After Utilization
	void Emptyfunction();

	//End Exisitng Timer
	UFUNCTION(BlueprintCallable, Category = "LatentAction")
	void FinishExistingTimer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Delegate Binders
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
