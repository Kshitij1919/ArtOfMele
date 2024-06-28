// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBlueprintNodes/CustomBlueprintAsyncActionBase.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Editor/EditorEngine.h"

UCustomBlueprintAsyncActionBase* UCustomBlueprintAsyncActionBase::ASyncCountSeconds(UObject* WorldContext, float Intervals, float FinalTime)
{
	UCustomBlueprintAsyncActionBase* BlueprintNode = NewObject<UCustomBlueprintAsyncActionBase>();
	BlueprintNode->TimerIntervals = FMath::Max(Intervals, 0.001f);
	BlueprintNode->TimerFinalTime = FinalTime;
	BlueprintNode->WorldContextObject = WorldContext;
	return BlueprintNode;
}

void UCustomBlueprintAsyncActionBase::Activate()
{
	World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	if (World == NULL && GEditor != NULL)
	{
		World = GEditor->GetEditorWorldContext().World();
	}

	if (World == NULL)
	{
		bOutSuccess = false;
		OutInfoMessage = "Custom Async Blueprint Action failed";
		OnFailed.Broadcast();
		FinishCountSeconds();
		return;
	}

	World->GetTimerManager().SetTimer(TimerHandle, this, &UCustomBlueprintAsyncActionBase::UpdateCountSeconds, TimerIntervals, true, -1.0f);
}

void UCustomBlueprintAsyncActionBase::CancelCountSeconds()
{
	bOutSuccess = true;
	OutInfoMessage = "Timer Cancelled";
	OnCancelled.Broadcast();
	FinishCountSeconds();
}



void UCustomBlueprintAsyncActionBase::UpdateCountSeconds()
{
	TimerCurrentTime += TimerIntervals;
	OnUpdated.Broadcast();
	OutInfoMessage = "Timer Updated ";

	if (TimerCurrentTime >= TimerFinalTime)
	{
		bOutSuccess = true;
		OutInfoMessage = "Timer Completed Successfully";
		OnCompleted.Broadcast();
		FinishCountSeconds();
	}
}

void UCustomBlueprintAsyncActionBase::FinishCountSeconds()
{
	if (TimerHandle.IsValid() && World != NULL)
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
		TimerHandle.Invalidate();
	}

	SetReadyToDestroy();
}
