// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/Player/InGamePlayerState.h"
#include "SurvivalProj/InGame/FieldActors/FieldActor.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	// ...
}

void UCharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterStatComponent, CurrentHP);
	DOREPLIFETIME(UCharacterStatComponent, bIsDead);
}

void UCharacterStatComponent::TakeDamage(float Damage)
{
	// 최소 대미지 1
	CurrentHP -= FMath::Max(1,Damage - CurrentDefencePoint);

	OnRep_CurrentHP();

	if (CurrentHP <= 0)
	{
		bIsDead = true;
	}
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (OwnerCharacter)
	{
		AInGamePlayerState* PlayerState = Cast<AInGamePlayerState>(OwnerCharacter->GetPlayerState());

		if (PlayerState)
		{
			MaxHP = PlayerState->GetMaxHp();
			CurrentAttackPoint = PlayerState->GetAttackPoint();
			CurrentDefencePoint = PlayerState->GetDefencePoint();

			CurrentHP = (PlayerState->GetCurrentHp() == 0.0f) ? PlayerState->GetMaxHp() : PlayerState->GetCurrentHp();
		}
	}
	else
	{
		OwnerFieldActor = Cast<AFieldActor>(GetOwner());

		if (OwnerFieldActor)
		{
			MaxHP = OwnerFieldActor->GetMaxHp();
			CurrentHP = MaxHP;
			CurrentDefencePoint = OwnerFieldActor->GetDefPoint();
		}
	}

	// ...
	
}


void UCharacterStatComponent::OnRep_CurrentHP()
{
	if (OwnerCharacter)
	{

	}
	else
	{
		if (OwnerFieldActor)
		{
			OwnerFieldActor->HPBarUpdate();
		}
	}
}

void UCharacterStatComponent::OnRep_bIsDead()
{
}

// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

