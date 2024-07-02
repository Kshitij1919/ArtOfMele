// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ARTOFMELE_API MathFunctions
{
public:
	MathFunctions();
	~MathFunctions();

	UFUNCTION(BlueprintCallable, Category = "CustomMathFunctions"
	meta = (ToolTip = "The function is used for updating the value and clamping it in given range. \n pass the sign along with UpdateIn value respectivle increment(+), decrement(-)"))
	template<typename T>
	static FORCEINLINE void UpdateAndClampValues(T& ValueToUpdate, T UpdateInValue, T Min, T Max) { ValueToUpdate = FMath::Clamp(ValueToUpdate + UpdateInValue, Min, Max); }
};
