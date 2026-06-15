// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuickSlotComponent.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/InGame/InGameHUD.h"
#include "SurvivalProj/InGame/Interfaces/ItemWidgetInterface.h"
#include "SurvivalProj/InGame/Item/WeaponItem.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"

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
	for (int i = 0; i < QuickSlots.Num(); i++)
	{

		if (QuickSlots[i] == nullptr)
		{
			
			UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
			NewWeapon->InitItem(WeaponTable, WeaponID);
			QuickSlots[i] = NewWeapon;

			if (CachedUIInterface)
			{
				FItemSlotData UpdatePacket;
				FWeaponItemStruct* ItemRow = WeaponTable->FindRow<FWeaponItemStruct>(WeaponID, TEXT("WeaponItemInit"));
				UpdatePacket.IconTexture = ItemRow->ItemIconTexture;
				UpdatePacket.Quantity = 1;
				UpdatePacket.ItemId = WeaponID;

				CachedUIInterface->UpdateItemSlot(i,UpdatePacket);
			}
			
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
	for (auto& slot : QuickSlots)
	{
		if (slot == nullptr)
		{
			return false;
		}
	}
	return true;
}

// Called when the game starts
void UPlayerQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	if (QuickSlots.Num() == 0)
	{
		QuickSlots.SetNum(MaxSlotCount);
	}

	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn != nullptr)
	{
		APlayerController* PC = Cast<APlayerController>(OwningPawn->GetController());
		if (PC != nullptr)
		{
			AInGameHUD* MyHUD = Cast<AInGameHUD>(PC->GetHUD());
			if (MyHUD != nullptr)
			{
				CachedUIInterface = Cast<IItemWidgetInterface>(MyHUD->GetPlayerQuickSlotInterface());
			}
		}
	}
	
}

// Called every frame
void UPlayerQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

