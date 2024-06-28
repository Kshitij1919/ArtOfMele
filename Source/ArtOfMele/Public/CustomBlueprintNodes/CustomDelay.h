// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LatentActions.h"
#include "CustomDelay.generated.h"

/**
 * 
 */

//this Enum Will be to create Input pins in our function
UENUM()
enum class ECountSecondsIntputPins : uint8
{
	Start,
	Increment,
	Cancel
};

//this enum will be used to create output pins in our function
UENUM()
enum class ECountSecondsOutputpins :uint8
{
	OnStarted, // to componsate for the lack of default output pin
	OnUpdated,
	OnCancelled,
	OnCompleted
};
	
UCLASS()
class ARTOFMELE_API UCustomDelay : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="WorldContext"> Variable to hold the object calling this function</param>
	/// <param name="LatentInfo"></param>
	/// <param name="InputPins"></param>
	/// <param name="OutputPins"></param>
	/// <param name="Intervals"></param>
	/// <param name="FinalTime"></param>
	/// <param name="OutCurrentTime"></param>
	/// <param name="bOutSuccess"></param>
	/// <param name="OutInfoMessage"></param>
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext", Latent, LatentInfo = "LatentInfo", ExpandEnumAsExecs = "InputPins, OutputPins"),
		Category = "latentAction|DelayNodes")
	static void LatentCountSeconds
	(
		UObject* WorldContext, 
		FLatentActionInfo LatentInfo,
		ECountSecondsIntputPins InputPins,
		ECountSecondsOutputpins& OutputPins,
		float Intervals,
		float FinalTime,
		float& OutCurrentTime,
		bool& bOutSuccess,
		FString& OutInfoMessage
		);
	
};


class FLatenetCountSeconds : public FPendingLatentAction
{
public :
	//Actions Interval
	float TimerInterval = 0.0f;

	//Actions Final Time
	float TimerFinalTime = 0.0f;

	//Action's current time (Reference so it updates the variables on the blueprint node)
	float& TimerCurrentTime;

	//Action's success state (Reference so it updates the variables on the blueprint node)
	bool& bSuccess;

	//Action's Infromation message (Reference so it updaters the variable on the blueprint node)
	FString& InfoMessage;

	
	//Flow Control
	
	// To only trigger execution pinj at desired intervals
	float TimerCurrentTimeInterval = 0.0f;

	//To Know if this was the first updateOperation call for thos action (to call the proper output pin)
	bool bFirstCall = true;

	// To know if the user wants to cancel the operation. To us it during next operation
	bool bWantToCancel = false;

	//required

	// Information required to complete the latent action properly
	FLatentActionInfo LatentActionInfo;

	//output pin to call (Reference so it updatres the variables on the blueprint node)
	ECountSecondsOutputpins& Output;


public: 
	//constructor
	FLatenetCountSeconds(FLatentActionInfo& LatentInfo, ECountSecondsOutputpins& OutputPins, float Intervals, float FinalTime, float& OutCurrentTime, bool& bOutsuccess, FString& OutInfoMessage)
		:LatentActionInfo(LatentInfo),
		Output(OutputPins),
		TimerInterval(Intervals),
		TimerFinalTime(FinalTime),
		TimerCurrentTime(OutCurrentTime),
		bSuccess(bOutsuccess),
		InfoMessage(OutInfoMessage)
	{
		Output = ECountSecondsOutputpins::OnStarted;
		TimerCurrentTime = 0.0f;
		bSuccess = false;
		InfoMessage = "";
	}

	//Callled EveryFrame
	virtual void UpdateOperation(FLatentResponse& Response) override;

#if  WITH_EDITOR
	//Description tht will appear above the blueprintnode  when debugging
	virtual FString GetDescription() const override
	{
		return FString::Printf(TEXT("Latent Count Seconds: %f / %f"), TimerCurrentTime, TimerFinalTime);
	}
#endif //  WITH_EDITOR

};
