// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LatentActions.h"
#include "ForLoopWithDelay.generated.h"

//Enums for Loop Input Pins
UENUM()
enum class EForLoopInputPins : uint8
{
	Execute,
	Break

};

//Enums for Loop Output Pins
UENUM()
enum class EForLoopOutputPins : uint8
{
	LoopBody,
	Completed

};

UCLASS()
class ARTOFMELE_API UForLoopWithDelay : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Custom for Loop wiht delay
	/// </summary>
	/// <param name="WorldContext">Variable to hold the Object callinmg this function. will be hidden in node</param>
	/// <param name="LatentInfo">Variable to hold information required to process a latent function. Will be hidden on the node</param>
	/// <param name="InputPins">Variable to hold diffrent input Pins. Will be hidden on the node</param>
	/// <param name="OutputPins">Variable to hold diffrent Output Pins. Will be hidden on the node</param>
	/// <param name="FirstIndex">Loop's First Index</param>
	/// <param name="LastIndex">Loop's Last Index</param>
	/// <param name="Delay">Loop's Delay between iteration</param>
	/// <param name="index">Loop's current Index</param>
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext", Latent, LatentInfo = "LatentInfo", ExpandEnumAsExecs = "InputPins,OutputPins"), Category = "LatentAction|Loops")
	static void CustomForLoopWithDelay(UObject* WorldContext, FLatentActionInfo LatentInfo, EForLoopInputPins InputPins, EForLoopOutputPins& OutputPins, int FirstIndex, int LastIndex, float Delay, int& index);
	
};

class FForLoopWithDelay :public FPendingLatentAction
{
public:
	//Loop's first Index
	int FirstIndex = 0;

	//Loop's Last Index
	int LastIndex = 0;

	//Loop's delay between iteration
	float Delay = 0.0f;

	//Loop's Current Timer
	float CurrentTime = 0.0f;

	//Loop's Current Index (Reference so it is updated)
	int& CurrentIndex;

	//to know if the user wants to break out of the loop. will break the next UpadteOpertaion
	bool bWantToBreak = false;
	
	//Information required to complete the latent action 
	FLatentActionInfo LatentActionInfo;

	//OtuputPin to call (reference so it is updated the variable on the blueprint node)
	EForLoopOutputPins& Output;

	//Constructor
	FForLoopWithDelay(FLatentActionInfo& LatentInfo, EForLoopOutputPins& OutputPins, int First, int Last, float TimerDelay, int& OutIndex)
		:LatentActionInfo(LatentInfo),
		Output(OutputPins),
		FirstIndex(First),
		LastIndex(Last),
		Delay(TimerDelay),
		CurrentIndex(OutIndex)
	{
		Output = EForLoopOutputPins::LoopBody;
		CurrentIndex = First - 1; //Logic Increments before calling first loop
		CurrentTime = TimerDelay; //Execute FirstLoop RightAway
	}

	//called everyfranme
	virtual void UpdateOperation(FLatentResponse& Response) override;

#if WITH_EDITOR
	//Description that will appear above blueprint node when debugging
	virtual FString GetDescription() const override
	{
		return FString::Printf(TEXT("Progress: %d / %d | Delay: %f / %f"), CurrentIndex, LastIndex, CurrentTime, Delay);
	}
#endif // WITH_EDITOR


};