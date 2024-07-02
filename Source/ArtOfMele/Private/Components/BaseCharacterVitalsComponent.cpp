// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseCharacterVitalsComponent.h"
#include "TimerManager.h" //Timer related Include
#include "CustomFunctionLibrary/MathFunctions.h" //Static Function include


// Costructors and tick functions
#pragma region Default Functions 
// Sets default values for this component's properties
UBaseCharacterVitalsComponent::UBaseCharacterVitalsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UBaseCharacterVitalsComponent::~UBaseCharacterVitalsComponent()
{
	StopStaminaRegenerationTimer();
}


// Called when the game starts
void UBaseCharacterVitalsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseCharacterVitalsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
#pragma endregion 

#pragma region Blueprint Getters
float UBaseCharacterVitalsComponent::GetCurrentHealth() const
{
	return Health;
}

float UBaseCharacterVitalsComponent::GetCurrentStamina() const
{
	return Stamina;
}
#pragma endregion

#pragma region BlueprintSetters
void UBaseCharacterVitalsComponent::UpdateCurrentHealth(const float ChangeInHealth)
{
	if (Health <= 0.0f || Health >= 100.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Update failed Value at Max/Min Capacity")));
		return;
	}
	MathFunctions::UpdateAndClampValues<float>(Health, ChangeInHealth, 0.0f, 100.0f);
}

void UBaseCharacterVitalsComponent::UpdateCurrentStamina(const float ChangeInStamina)
{
	if (Stamina <= 0.0f || Stamina >= 100.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Update failed Value at Max/Min Capacity")));
		return;
	}
	MathFunctions::UpdateAndClampValues<float>(Stamina,ChangeInStamina, 0.0f, 100.0f);
}
#pragma endregion

#pragma region Timer Functions
void UBaseCharacterVitalsComponent::StartStaminaRegenerationTimer()
{
	//return if not able to get world
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("World Inavlid cannot start Timer"));
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(StaminaUpdateTimerHandle, this, &UBaseCharacterVitalsComponent::RegenerateStaimna, StaminaRegenerationRate, true);
}
void UBaseCharacterVitalsComponent::StopStaminaRegenerationTimer()
{
	//return if not able to get world
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("World Inavlid cannot Stop Timer"));
		return;
	}
	//return if Timer handle invalid
	if (!StaminaUpdateTimerHandle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Timer Invalid"));
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(StaminaUpdateTimerHandle);
	StaminaUpdateTimerHandle.Invalidate();
	
}
void UBaseCharacterVitalsComponent::RegenerateStaimna()
{
	UpdateCurrentStamina(StaminaRegenerationValue);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Stamina: %f"), Stamina));
	if (Stamina >= 100)
	{
		StopStaminaRegenerationTimer();
	}
}
#pragma endregion
