// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBlueprintNodes/CustomDelay.h"
#include "Engine/LatentActionManager.h"
#include "Editor.h"

void UCustomDelay::LatentCountSeconds(UObject* WorldContext, FLatentActionInfo LatentInfo, ECountSecondsIntputPins InputPins, ECountSecondsOutputpins& OutputPins, float Intervals, float FinalTime, float& OutCurrentTime, bool& bOutSuccess, FString& OutInfoMessage)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);

	if (World == nullptr && GEditor != nullptr)
	{
		World = GEditor->GetEditorWorldContext().World();
	}

	if (World == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = "Latent Count seconds Failed - World is not valid.";

		UE_LOG(LogTemp, Error, TEXT("%s"), *OutInfoMessage);
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FLatenetCountSeconds* ExistingAction = LatentActionManager.FindExistingAction<FLatenetCountSeconds>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (InputPins == ECountSecondsIntputPins::Start)
	{
		if (ExistingAction == nullptr)
		{
			FLatenetCountSeconds* Action = new FLatenetCountSeconds(LatentInfo, OutputPins, Intervals, FinalTime, OutCurrentTime, bOutSuccess, OutInfoMessage);
			LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
		}
	}

	else if (InputPins == ECountSecondsIntputPins::Increment)
	{
		if (ExistingAction != nullptr)
		{
			ExistingAction->TimerCurrentTime += 1.0f;
		}
	}

	else if (InputPins == ECountSecondsIntputPins::Cancel)
	{
		if (ExistingAction != nullptr)
		{
			ExistingAction->bWantToCancel = true;
		}
	}
	
}

void FLatenetCountSeconds::UpdateOperation(FLatentResponse& Response)
{
	if (bWantToCancel)
	{
		bSuccess = true;
		InfoMessage = "Latent Count Seconds Succeeded - Cancelled by user.";

		Output = ECountSecondsOutputpins::OnCancelled;
		Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
		return;
	}
	TimerCurrentTimeInterval += Response.ElapsedTime();

	bool bIntervalReached = TimerCurrentTimeInterval >= TimerInterval;

	if (bIntervalReached)
	{
		TimerCurrentTime += TimerInterval;
		TimerCurrentTimeInterval -= TimerInterval;
	}

	if (bFirstCall)
	{
		bFirstCall = false;

		bSuccess = true;
		InfoMessage = "Latent CountSeconds Started...";

		Output = ECountSecondsOutputpins::OnStarted;
		Response.TriggerLink(LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
		return;
	}

	if (TimerCurrentTime >= TimerFinalTime)
	{
		bSuccess = true;
		Output = ECountSecondsOutputpins::OnCompleted;
		Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
		return;
	}

	if (bIntervalReached)
	{
		InfoMessage = "Interval Reached...";
		Output = ECountSecondsOutputpins::OnUpdated;
		Response.TriggerLink(LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
	}
}
