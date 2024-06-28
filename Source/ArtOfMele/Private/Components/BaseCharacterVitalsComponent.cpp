// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseCharacterVitalsComponent.h"

// Sets default values for this component's properties
UBaseCharacterVitalsComponent::UBaseCharacterVitalsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

float UBaseCharacterVitalsComponent::GetCurrentHealth() const
{
	return Health;
}

float UBaseCharacterVitalsComponent::GetCurrentStamina() const
{
	return Stamina;
}

void UBaseCharacterVitalsComponent::UpdateCurrentHealth(const float ChangeInHealth)
{
	Health += ChangeInHealth;
}

void UBaseCharacterVitalsComponent::UpdateCurrentStamina(const float ChangeInStamina)
{
	Stamina += ChangeInStamina;
}

