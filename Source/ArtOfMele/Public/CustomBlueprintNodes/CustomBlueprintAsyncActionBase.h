// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CustomBlueprintAsyncActionBase.generated.h"

/**
 * 
 */
//Delegate used to creaste output pins
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncCountSecondsOutputPin);

UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncAction))
class ARTOFMELE_API UCustomBlueprintAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext", BlueprintInternalUseOnly = "true"), Category = "LatentAction|CustomLatentNodes")
	static UCustomBlueprintAsyncActionBase* ASyncCountSeconds(UObject* WorldContext, float Intervals, float FinalTime);
	
	//Output pin called when Timer is updated
	UPROPERTY(BlueprintAssignable, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|OutputPins")
	FAsyncCountSecondsOutputPin OnUpdated;
	
	//Output pin called when Timer is Cancelled
	UPROPERTY(BlueprintAssignable, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|OutputPins")
	FAsyncCountSecondsOutputPin OnCancelled;

	//Output pin called when Timer is Completed
	UPROPERTY(BlueprintAssignable, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|OutputPins")
	FAsyncCountSecondsOutputPin OnCompleted;

	//Output pin called when Timer Fails
	UPROPERTY(BlueprintAssignable, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|OutputPins")
	FAsyncCountSecondsOutputPin OnFailed;

private:
	virtual void Activate() override;

public:
	//Action's Interval
	UPROPERTY(BlueprintReadOnly, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|InputVariables")
	float TimerIntervals = 0.0f;

	//Action's final Time
	UPROPERTY(BlueprintReadOnly, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|InputVariables")
	float TimerFinalTime = 0.0f;

	//Action's Current Time
	UPROPERTY(BlueprintReadOnly, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|InputVariables")
	float TimerCurrentTime = 0.0f;

	//Action's Success state
	UPROPERTY(BlueprintReadOnly, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds")
	bool bOutSuccess = false;

	//Action's Infromation message
	UPROPERTY(BlueprintReadOnly, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds|InputVariables")
	FString OutInfoMessage = "";


public:
	//Cancel the Action
	UFUNCTION(BlueprintCallable, Category = "LatentAction|CustomLatentNode|ASyncCountSeconds")
	void CancelCountSeconds();


private:
	// update timer
	void UpdateCountSeconds();

	//finish Timer and cleanup
	void FinishCountSeconds();

	UObject* WorldContextObject;
	UWorld* World;
	FTimerHandle TimerHandle;
};
