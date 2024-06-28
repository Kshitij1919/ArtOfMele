// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseCombatComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
//#include "Kismet/KismetSystemLibrary.h
//LatentAction Includes
#include "Engine.h"
#include "Engine/World.h"
#include "Editor/EditorEngine.h"




// Sets default values for this component's properties
UBaseCombatComponent::UBaseCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}





void UBaseCombatComponent::Emptyfunction()
{
}

void UBaseCombatComponent::FinishExistingTimer()
{
	if (TimerHandle.IsValid() && World != NULL)
	{
		TimerHandle.Invalidate();
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

}



// Called when the game starts
void UBaseCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UBaseCombatComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Interuppted at CurrentIndex: %d"), CurrentAttackIndex));

	}
	else
	{
		CurrentAttackIndex++;
		TempAttackSequencer(AttackSummary, SkeletalMeshComp);
	}
}

// Called every frame
void UBaseCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseCombatComponent::PerfromAttack_Implementation(UObject* WorldContext, const TArray<FAttackDetails>& AttackDetail, const USkeletalMeshComponent* MeshComp)
{

	for (FAttackDetails attackdetail : AttackDetail)
	{
		if (UAnimMontage** MontageToPlay = AttackMappings.Find(attackdetail))
		{
			if (UAnimInstance* Animinstance = MeshComp->GetAnimInstance())
			{
				
				float MontageLength = Animinstance->Montage_Play(*MontageToPlay, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f);
				if (MontageLength > 0.0f)
				{
					/*FLatentActionInfo  LatentActionhInfo;
					LatentActionhInfo.Linkage = 0;
					LatentActionhInfo.CallbackTarget = this->GetOwner();
					LatentActionhInfo.ExecutionFunction = "PerfromAttack_Implementation";
					LatentActionhInfo.UUID = GetUniqueID();
					UKismetSystemLibrary::Delay(GetWorld(), MontageLength, LatentActionhInfo);*/

					World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
					if (World == NULL)
					{
						continue;
					}
					FinishExistingTimer();
					World->GetTimerManager().SetTimer(TimerHandle, this, &UBaseCombatComponent::Emptyfunction, MontageLength, true);

				}

			}
		}
	}
	
}

#pragma region Combat Comp Function
void UBaseCombatComponent:: TempAttackSequencer(const TArray<FAttackDetails>& AttackDetails, const USkeletalMeshComponent* MeshComp)
{
	if (AttackSummary != AttackDetails)
	{
		AttackSummary = AttackDetails;
	}
	if (SkeletalMeshComp != MeshComp)
	{
		SkeletalMeshComp = MeshComp;
	}
	
	
	//checking if the current attack index has not excedded the attackdetails array size
	if (CurrentAttackIndex >= AttackDetails.Num())
	{
		CurrentAttackIndex = 0;
		return;
	}

	//matching the attack detail provided by the designer with attackmapping key to get the appropriate Montage;
	UAnimMontage** MontageToPlay = AttackMappings.Find(AttackDetails[CurrentAttackIndex]);
	UAnimInstance* MeshCompAnimInstance = MeshComp->GetAnimInstance();
	
	// retruning if montage or anim instance is invalid
	if (MeshCompAnimInstance == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Anim Instance"));
		return;
	}
	if (MontageToPlay == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Anim Montage at AttackDetail Index:- %d"), CurrentAttackIndex);
		return;
	}

	//Play the Anim montage and store the length of the montage
	const float MontageLength = MeshCompAnimInstance->Montage_Play(*MontageToPlay,1.0f, EMontagePlayReturnType::MontageLength, 0.0f);
	bool bMontagePlayedSuccessfully = (MontageLength > 0.0f);
	if (bMontagePlayedSuccessfully)
	{ 
		MontageEndedDelegate.BindUObject(this, &UBaseCombatComponent::OnMontageEnded);
		MeshCompAnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, *MontageToPlay);
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("CurrentIndex: %d"), CurrentAttackIndex));
		
	}
	else
	{
		//MonmtageInteruppted Code here
		OnMontageEnded(*MontageToPlay, true);
	}
}
#pragma endregion


#pragma region Update State Function
void UBaseCombatComponent:: UpdateIsCharacterDodging_Implementation(const bool Dodging)
{
	bIsCharacterdodging = Dodging;
}

void UBaseCombatComponent::UpdateIsCharacterBlocking_Implementation(const bool Blocking)
{
	bIsCharacterBlocking = Blocking;
}

void UBaseCombatComponent::UpdateCanPlayMontage_Implementation(const bool canplaymontage)
{
	bCanPlayAnimMontage = canplaymontage;
}

void UBaseCombatComponent::UpdateIsCharacterInCombat_Implementation(const bool bShouldCharacterbeInCombat)
{
	bIsInCombat = bShouldCharacterbeInCombat;
}

void UBaseCombatComponent::UpdateCharacterCombatStates_Implementation(const ECombatStates NewCombatState)
{
	CombatState = NewCombatState;
}
#pragma endregion


#pragma region Getter Functions
bool UBaseCombatComponent::GetIsInCombat() const
{
	return bIsInCombat;
}

ECombatStates UBaseCombatComponent::GetCombatState() const
{
	return CombatState;
}

bool UBaseCombatComponent::GetIsCharacterDodging() const
{
	return bIsCharacterdodging;
}
bool UBaseCombatComponent::GetIsCharacterBlocking() const
{
	return bIsCharacterBlocking;
}
bool UBaseCombatComponent::CanPlayMontage() const
{
	return bCanPlayAnimMontage;
}
#pragma endregion




