// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryComponent.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/PlayerEquipmentComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/Data/Enums/EWeaponEquipState.h"
#include "SurvivalProj/InGame/InGameHUD.h"
#include "SurvivalProj/InGame/Item/WeaponItem.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "SurvivalProj/InGame/Item/EquipWeapon.h"

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
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UPlayerInventoryComponent, InventorySlots, COND_OwnerOnly);
}

void UPlayerInventoryComponent::ServerRegisterWeaponToEmptySlot_Implementation(FName WeaponID)
{
	if (WeaponTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] WeaponTable 자산이 바인딩되지 않았습니다."));
		return;
	}

	// 비어있는 슬롯에 아이템 추가
	for (int i = 0; i < InventorySlots.Num(); i++)
	{

		if (InventorySlots[i] == nullptr)
		{

			UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
			NewWeapon->InitItem(WeaponTable, WeaponID);
			InventorySlots[i] = NewWeapon;

			// 새로 만든 서브오브젝트를 Replicated 등록
			AddReplicatedSubObject(NewWeapon);

			ClientNotifyWeaponRegistered(i, WeaponID);

			break;

		}
	}
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


void UPlayerInventoryComponent::RegisterWidgetReference(UPlayerInventoryWidget* WidgetRef)
{
}

// Called when the game starts
void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InventorySlots.Num() == 0)
	{
		InventorySlots.SetNum(MaxSlotCount);
	}
	OwnerCharacter = Cast<APlayerCharacter>(GetOwner());

	EquipmentComponent = OwnerCharacter->GetComponentByClass<UPlayerEquipmentComponent>();
	
}


// Called every frame
void UPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

