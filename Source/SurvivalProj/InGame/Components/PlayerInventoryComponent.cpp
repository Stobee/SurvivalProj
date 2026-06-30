// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryComponent.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/InGamePlayerController.h"
#include "SurvivalProj/InGame/Components/PlayerEquipmentComponent.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/Data/Enums/EWeaponEquipState.h"
#include "SurvivalProj/InGame/InGameHUD.h"
#include "SurvivalProj/InGame/Item/WeaponItem.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "SurvivalProj/InGame/Item/EquipWeapon.h"
#include "SurvivalProj/InGame/Item/FieldItem.h"

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


void UPlayerInventoryComponent::ClientNotifyWeaponRegistered_Implementation(int32 SlotIndex, FName Id)
{
	if (CachedInventoryWidget)
	{
		FItemSlotData UpdatePacket;
		FWeaponItemStruct* ItemRow = WeaponTable->FindRow<FWeaponItemStruct>(Id, TEXT("WeaponItemInit"));
		UpdatePacket.IconTexture = ItemRow->ItemIconTexture;
		UpdatePacket.Quantity = 1;
		UpdatePacket.ItemId = Id;
		UpdatePacket.SlotNumber = SlotIndex;
		UpdatePacket.ItemType = EItemType::Weapon;

		CachedInventoryWidget->UpdateItemSlot(SlotIndex, UpdatePacket);
	}

}

bool UPlayerInventoryComponent::RegisterWeaponToEmptySlot(FName WeaponId)
{
	if (WeaponTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] WeaponTable 자산이 바인딩되지 않았습니다."));
		return false;
	}

	// 비어있는 슬롯에 아이템 추가
	for (int i = 0; i < InventorySlots.Num(); i++)
	{

		if (InventorySlots[i] == nullptr)
		{
			UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
			NewWeapon->InitItem(WeaponTable, WeaponId);
			InventorySlots[i] = NewWeapon;

			// 새로 만든 서브오브젝트를 Replicated 등록
			AddReplicatedSubObject(NewWeapon);

			ClientNotifyWeaponRegistered(i, WeaponId);

			return true;

		}
	}

	return false;
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

void UPlayerInventoryComponent::RemoveSlotItem(int32 SlotIndex)
{
	ServerRemoveSlotItem(SlotIndex);
}

void UPlayerInventoryComponent::ServerRemoveSlotItem_Implementation(int32 SlotIndex)
{
	RemoveReplicatedSubObject(InventorySlots[SlotIndex]);

	// 가비지 컬렉터에 등록
	// TArray의 Remove는 사용금지
	UObject* TargetObject = InventorySlots[SlotIndex];
	if (TargetObject)
	{
		TargetObject->MarkAsGarbage();
	}


	InventorySlots[SlotIndex] = nullptr;

	ClientNotifySlotItemRemoved(SlotIndex);
}

void UPlayerInventoryComponent::ClientNotifySlotItemRemoved_Implementation(int32 SlotIndex)
{
	if (CachedInventoryWidget)
	{
		CachedInventoryWidget->RemoveItemSlot(SlotIndex);
	}
}

bool UPlayerInventoryComponent::bIsInventorySlotFull()
{
	for (auto& slot : InventorySlots)
	{
		if (slot == nullptr)
		{
			return false;
		}
	}
	return true;
}

void UPlayerInventoryComponent::VisibleInventoryWidget()
{
	if (CachedInventoryWidget)
	{
		static bool bIsFlip = true;

		if (bIsFlip)
		{
			CachedInventoryWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			if (CachedPlayerController)
			{
				CachedPlayerController->bShowMouseCursor = true;

				// UI 입력 모드 구조체 (기본 값)
				FInputModeGameAndUI InputModeData;

				InputModeData.SetHideCursorDuringCapture(false);
				
				CachedPlayerController->SetInputMode(InputModeData);

				OwnerCharacter->ActState = EPlayerActState::UsingInventory;
				
			}

		}
		else
		{
			CachedInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

			if (CachedPlayerController)
			{
				CachedPlayerController->bShowMouseCursor = false;

				// 게임 입력 모드 구조체 (기본 값)
				FInputModeGameOnly InputModeData;

				CachedPlayerController->SetInputMode(InputModeData);

				OwnerCharacter->ActState = EPlayerActState::Movable;

			}
		}

		// true는 false로, false는 true로 0프레임 만에 환장하여 다음 격발 타이밍을 선제 예약한다.
		bIsFlip = !bIsFlip;
	}
}


void UPlayerInventoryComponent::RegisterWidgetReference(UPlayerInventoryWidget* WidgetRef)
{
	if (WidgetRef == nullptr)
	{
		return;
	}

	CachedInventoryWidget = WidgetRef;
}

void UPlayerInventoryComponent::UseItem(int32 SlotNum)
{
	// 널 포인터 접근을 차단
	if (!InventorySlots[SlotNum]) return;

	switch (InventorySlots[SlotNum]->GetItemType())
	{
	case (EItemType::Weapon):
	{
		ServerEquipWeapon(InventorySlots[SlotNum]->GetItemID());

		break;
	}
	case (EItemType::Armor):
	{

		break;
	}
	case (EItemType::Potion):
	{

		break;
	}

	case (EItemType::Resource):
	{

		break;
	}
	case (EItemType::None):
	{
		break;
	}
	}
}

void UPlayerInventoryComponent::ServerEquipWeapon_Implementation(FName WeaponId)
{
	if (OwnerCharacter->HasAuthority())
	{
		EquipmentComponent->UpdateWeaponSlot(WeaponId);

		OwnerCharacter->MulticastPlayEquipWeaponMontage();
	}
}

bool UPlayerInventoryComponent::DropItem(int32 SlotNum, FVector DropLocation)
{
	UItemInstance* TargetItem = InventorySlots[SlotNum];

	switch (TargetItem->GetItemType())
	{
	case (EItemType::Weapon):
	{
		if (!WeaponTable) return false;
		FWeaponItemStruct* ItemRow = WeaponTable->FindRow<FWeaponItemStruct>(TargetItem->GetItemID(), TEXT("WeaponItemDrop"));

		UWeaponItem* TargetWeapon = Cast<UWeaponItem>(TargetItem);

		// 아이템 스폰 로직

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Owner = nullptr;

		AFieldItem* DropFieldItem = GetWorld()->SpawnActor<AFieldItem>(ItemRow->FieldWeaponActor, DropLocation, FRotator::ZeroRotator, SpawnParams);

		FItemSlotData UpdatePacket;

		UpdatePacket.ItemId = TargetItem->GetItemID();
		UpdatePacket.ItemType = EItemType::Weapon;
		UpdatePacket.Quantity = TargetItem->GetQuantity();
		UpdatePacket.AttackPoint = TargetWeapon->GetWeaponAP();
		UpdatePacket.CurrentDuravility = TargetWeapon->GetWeaponDuravility();
		UpdatePacket.EnhencementLevel = TargetWeapon->GetWeaponEnhencementLevel();

		DropFieldItem->SetItemState(UpdatePacket);

		return true;

		break;
	}
	case (EItemType::Armor):
	{
		break;
	}
	case (EItemType::Potion):
	{
		break;
	}
	case (EItemType::Resource):
	{
		break;
	}
	}

	return false;
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

	CachedPlayerController = Cast<AInGamePlayerController>(OwnerCharacter->GetController());

	EquipmentComponent = OwnerCharacter->GetComponentByClass<UPlayerEquipmentComponent>();
	
}


// Called every frame
void UPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

