// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBlueprintNodes/ForLoopWithDelay.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Editor/EditorEngine.h"

void UForLoopWithDelay::CustomForLoopWithDelay(UObject* WorldContext, FLatentActionInfo LatentInfo, EForLoopInputPins InputPins, EForLoopOutputPins& OutputPins, int FirstIndex, int LastIndex, float Delay, int& index)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);

	if (World == NULL && GEditor != NULL)
	{
		World = GEditor->GetEditorWorldContext().World();
	}

	if (World == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("For loop with delay failed = World Not Valid"));
		return;
	}
	
	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FForLoopWithDelay* ExistingAction = LatentActionManager.FindExistingAction<FForLoopWithDelay>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (InputPins == EForLoopInputPins::Execute)
	{
		if (ExistingAction == NULL)
		{
			FForLoopWithDelay* Action = new FForLoopWithDelay(LatentInfo, OutputPins, FirstIndex, LastIndex, Delay, index);
			LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
		}
	}

	else if (InputPins == EForLoopInputPins::Break)
	{
		if (ExistingAction != NULL)
		{
			ExistingAction->bWantToBreak = true;
		}
	}
	//NoitExecutionPin after this
}

void FForLoopWithDelay::UpdateOperation(FLatentResponse& Response)
{
	if (bWantToBreak || CurrentIndex >= LastIndex)
	{
		Output = EForLoopOutputPins::Completed;
		Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
		return;
	}

	CurrentTime += Response.ElapsedTime();

	if (CurrentTime >= Delay)
	{
		CurrentTime -= Delay;
		CurrentIndex++;
		Output = EForLoopOutputPins::LoopBody;
		Response.TriggerLink(LatentActionInfo.ExecutionFunction, LatentActionInfo.UUID, LatentActionInfo.CallbackTarget);
		return;
	}
}
