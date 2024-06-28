// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCharacterVitalsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ARTOFMELE_API UBaseCharacterVitalsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseCharacterVitalsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*Core Variables*/
#pragma region Core Variables
	UPROPERTY(EditDefaultsOnly, BlueprintSetter = UpdateCurrentHealth, BlueprintGetter = GetCurrentHealth, meta = (ClampMin = 0.0f, ClampMax = 100.0f), Category = "Vitals")
	float Health = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintSetter = UpdateCurrentStamina,  BlueprintReadWrite, BlueprintGetter = GetCurrentHealth, meta = (ClampMin = 0.0f, ClampMax = 100.0f), Category = "Vitals")
	float Stamina = 100;
#pragma endregion

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintGetter)
	float GetCurrentStamina() const;

	UFUNCTION(BlueprintCallable, meta =(ToolTip = "this Function handles both reducing and increasing Health. pass the sign along with value (+ for increase, - for Decrease)"), Category = "Update States")
	void UpdateCurrentHealth(const float ChangeInHealth = 0.0f);

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "this Function handles both reducing and increasing Stamina. pass the sign along with value (+ for increase, - for Decrease)"), Category = "Update States")
	void UpdateCurrentStamina(const float ChangeInStamina = 0.0f);
		
};
