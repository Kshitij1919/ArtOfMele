// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCharacterVitalsComponent.generated.h"

struct FTimerHandle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ARTOFMELE_API UBaseCharacterVitalsComponent : public UActorComponent
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this component's properties
	UBaseCharacterVitalsComponent();

	~UBaseCharacterVitalsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private: 

#pragma region Stamina Timer Variables
	//the timer variable for Stamina Regenration.
	FTimerHandle StaminaUpdateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, ClampMin = 0.25f, ClampMax = 1.0f), Category = "Timer|StaminaRegeneration",
		meta = (ToolTip = "The Rate at which Stamina will Regenerate"))
	float StaminaRegenerationRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, ClampMin = 10.0f, ClampMax = 30.0f), Category = "Timer|StaminaRegeneration",
		meta = (ToolTip = "The Value at which Stamina will Regenerate"))
	float StaminaRegenerationValue = 10.0f;
#pragma endregion


#pragma region Core Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintSetter = UpdateCurrentHealth, BlueprintGetter = GetCurrentHealth, meta = (ClampMin = 0.0f, ClampMax = 100.0f, AllowPrivateAccess = true), Category = "Vitals")
	float Health = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintSetter = UpdateCurrentStamina, BlueprintGetter = GetCurrentStamina, meta = (ClampMin = 0.0f, ClampMax = 100.0f), Category = "Vitals")
	float Stamina = 100;
#pragma endregion

	/*Variable Modifers*/
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (ClampMin = 0.0f, ClampMax = 1.0f, AllowPrivateAccess = "true"), category = "Combat|CoreVariables")
	float HealthDamageModifier = 1.0f;

public: 
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Blueprint Getters
	UFUNCTION(BlueprintGetter)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintGetter)
	float GetCurrentStamina() const;
#pragma endregion

#pragma region Blueprint Setter
	UFUNCTION(BlueprintCallable, meta =(ToolTip = "this Function handles both reducing and increasing Health. Pass the sign along with value (+ for increase, - for Decrease)"), Category = "Update States")
	void UpdateCurrentHealth(const float ChangeInHealth = 0.0f);

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "this Function handles both reducing and increasing Stamina. Pass the sign along with value (+ for increase, - for Decrease)"), Category = "Update States")
	void UpdateCurrentStamina(const float ChangeInStamina = 0.0f);
#pragma endregion	

#pragma region Timer Function 
	UFUNCTION(BlueprintCallable, Category = "TimerFunction|Stamina")
	void StartStaminaRegenerationTimer();

	UFUNCTION(BlueprintCallable, Category = "TimerFunction|Stamina")
	void StopStaminaRegenerationTimer();
#pragma endregion 

private:
#pragma region Timer Function
	void RegenerateStaimna();
#pragma endregion
//Update Values
	 
};
