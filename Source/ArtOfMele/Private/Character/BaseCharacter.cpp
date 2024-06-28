// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Data/GlobalData.h"
#include "Kismet/GameplayStatics.h" //delta seconds include

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LocomotionStates = ECharacterLocomotionStates::WALKING;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ABaseCharacter::CalculateAcceleration_Implementation() const
{
	return (this->GetVelocity() - PreviousVelocity) / UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
}



FCharacterValues ABaseCharacter::GetCharacterEssentialValues_Implementation()
{
	return FCharacterValues();
}

FCharacterStates ABaseCharacter::GetCharacterStates_Implementation()
{
	return FCharacterStates();
}



