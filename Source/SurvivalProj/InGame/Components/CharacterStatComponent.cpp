// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalProj/InGame/MainCharacter.h"

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

}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AMainCharacter>(GetOwner());

	if (OwnerCharacter)
	{
		
	}

	// ...
	
}


void UCharacterStatComponent::OnRep_CurrentHP(float OldHP)
{
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

