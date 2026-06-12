// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuickSlotComponent.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/InGame/Item/WeaponItem.h"

// Sets default values for this component's properties
UPlayerQuickSlotComponent::UPlayerQuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPlayerQuickSlotComponent::RegisterWeaponToEmptySlot(FName WeaponID)
{
	if (WeaponTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] WeaponTable 자산이 바인딩되지 않았습니다."));
		return;
	}
	// 비어있는 슬롯에 아이템 추가
	for (auto& slot : QuickSlots)
	{
		if (!slot)
		{
			UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
			NewWeapon->InitItem(WeaponTable, WeaponID);
			slot = NewWeapon;
			
			break;
		}
	}
}

void UPlayerQuickSlotComponent::RegisterArmorToEmptySlot(FName ArmorId)
{
	if (ArmorTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] ArmorTable 자산이 바인딩되지 않았습니다."));
		return;
	}
}

void UPlayerQuickSlotComponent::RegisterResourceToEmptySlot(FName ResourceId, int32 Quantity)
{
	if (ResourceTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] ResourceTable 자산이 바인딩되지 않았습니다."));
		return;
	}
}

void UPlayerQuickSlotComponent::RegisterPotionToEmptySlot(FName PotionId, int32 Quantity)
{
	if (PotionTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] PotionTable 자산이 바인딩되지 않았습니다."));
		return;
	}
}

void UPlayerQuickSlotComponent::ExecuteSlotAction(int32 SlotIndex)
{

}

bool UPlayerQuickSlotComponent::bIsQuickSlotFull()
{
	if (QuickSlots.Num() == MaxSlotCount) return true;
	return false;
}

// Called when the game starts
void UPlayerQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UPlayerQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

