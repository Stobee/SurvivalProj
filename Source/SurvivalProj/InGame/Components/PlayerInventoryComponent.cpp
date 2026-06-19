// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;

	// ...
}

void UPlayerInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

void UPlayerInventoryComponent::ServerRegisterWeaponToEmptySlot_Implementation(FName WeaponID)
{
}


void UPlayerInventoryComponent::ClientNotifyWeaponRegistered_Implementation(int32 SlotIndex, FName Id)
{

}

void UPlayerInventoryComponent::RegisterWeaponToEmptySlot(FName WeaponId)
{

}

void UPlayerInventoryComponent::RegisterArmorToEmptySlot(FName ArmorId)
{

}

void UPlayerInventoryComponent::RegisterResourceToEmptySlot(FName ResourceId, int32 Quantity)
{ 

}

void UPlayerInventoryComponent::RegisterPotionToEmptySlot(FName PotionId, int32 Quantity)
{

}

bool UPlayerInventoryComponent::bIsInventorySlotFull()
{
	if (InventorySlots.Num() == MaxSlotCount) return true;
	return false;
}


// Called when the game starts
void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

