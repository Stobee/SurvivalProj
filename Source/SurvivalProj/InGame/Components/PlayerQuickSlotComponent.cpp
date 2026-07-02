// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuickSlotComponent.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/PlayerEquipmentComponent.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/Data/DataTableStructs/ArmorItemStruct.h"
#include "SurvivalProj/Data/DataTableStructs/ResourceItemStruct.h"
#include "SurvivalProj/Data/DataTableStructs/PotionItemStruct.h"
#include "SurvivalProj/Data/Enums/EWeaponEquipState.h"
#include "SurvivalProj/InGame/InGameHUD.h"
#include "SurvivalProj/InGame/Item/WeaponItem.h"
#include "SurvivalProj/InGame/Item/ArmorItem.h"
#include "SurvivalProj/InGame/Item/ResourceItem.h"
#include "SurvivalProj/InGame/Item/PotionItem.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "SurvivalProj/InGame/Item/EquipWeapon.h"
#include "SurvivalProj/InGame/Item/EquipArmor.h"
#include "SurvivalProj/InGame/Item/FieldItem.h"






// Sets default values for this component's properties
UPlayerQuickSlotComponent::UPlayerQuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	// ...
}

void UPlayerQuickSlotComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 소유자 로컬 클라이언트에게만 패킷을 전송하도록 조건부 복제 마감
	DOREPLIFETIME_CONDITION(UPlayerQuickSlotComponent, QuickSlots, COND_OwnerOnly);
}


/*bool UPlayerQuickSlotComponent::ServerRegisterWeaponToEmptySlot_Validate(FName WeaponId)
{
	// 예시 코드 이후 수정 필요
	// 1. 하드웨어 데이터테이블 누수 선제 수사
	if (WeaponTable == nullptr)
	{
		// 서버 자체 데이터가 유실된 것이므로 우선 true로 패싱하여 
		// 클라이언트가 억울하게 해커로 오인되어 튕기는 대재앙을 방어한다.
		return true;
	}

	// 2.[해킹 위조 패킷 정밀 수사]
	// 클라이언트가 보내온 WeaponId 완장이 진짜 우리 무기 데이터테이블 장부에 실존하는지 수색한다.
	FWeaponItemStruct* ItemRow = WeaponTable->FindRow<FWeaponItemStruct>(WeaponId, TEXT("Security_Validate"));

	// 장부에 없는 가짜 ID일 경우 false
	// 언리얼 엔진 커널이 해당 패킷을 차단하고 위조범 클라이언트를 즉시 가상 세계에서 강제 영구 철거(Kick)한다.
	return ItemRow != nullptr;
}*/




void UPlayerQuickSlotComponent::ClientNotifyItemRegistered_Implementation(int32 SlotIndex, FName Id, EItemType Type, int32 Quantity = 1)
{
	if (CachedQuickSlotWidget)
	{
		FItemSlotData UpdatePacket;

		switch (Type)
		{
		case (EItemType::Weapon) :
		{
			FWeaponItemStruct* ItemRow = WeaponTable->FindRow<FWeaponItemStruct>(Id, TEXT("WeaponItemInit"));
			UpdatePacket.IconTexture = ItemRow->ItemIconTexture;
			UpdatePacket.Quantity = Quantity;
			UpdatePacket.ItemId = Id;
			UpdatePacket.SlotNumber = SlotIndex;
			UpdatePacket.ItemType = EItemType::Weapon;

			break;
		}
		case (EItemType::Armor) :
		{
			FArmorItemStruct* ItemRow = ArmorTable->FindRow<FArmorItemStruct>(Id, TEXT("ArmorItemInit"));
			UpdatePacket.IconTexture = ItemRow->ItemIconTexture;
			UpdatePacket.Quantity = Quantity;
			UpdatePacket.ItemId = Id;
			UpdatePacket.SlotNumber = SlotIndex;
			UpdatePacket.ItemType = EItemType::Armor;

			break;
		}
		case (EItemType::Resource) :
		{
			FResourceItemStruct* ItemRow = ResourceTable->FindRow<FResourceItemStruct>(Id, TEXT("ResourceItemInit"));
			UpdatePacket.IconTexture = ItemRow->ItemIconTexture;
			UpdatePacket.Quantity = Quantity;
			UpdatePacket.ItemId = Id;
			UpdatePacket.SlotNumber = SlotIndex;
			UpdatePacket.ItemType = EItemType::Resource;
			
			break;
		}
		case (EItemType::Potion) :
		{
			FPotionItemStruct* ItemRow = PotionTable->FindRow<FPotionItemStruct>(Id, TEXT("PotionItemInit"));
			UpdatePacket.IconTexture = ItemRow->ItemIconTexture;
			UpdatePacket.Quantity = Quantity;
			UpdatePacket.ItemId = Id;
			UpdatePacket.SlotNumber = SlotIndex;
			UpdatePacket.ItemType = EItemType::Potion;

			break;
		}
		}

		CachedQuickSlotWidget->UpdateItemSlot(SlotIndex, UpdatePacket);
	}
}

bool UPlayerQuickSlotComponent::RegisterWeaponToEmptySlot(FName WeaponID)
{
	if (WeaponTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] WeaponTable 자산이 바인딩되지 않았습니다."));
		return false;
	}

	// 비어있는 슬롯에 아이템 추가
	for (int i = 0; i < QuickSlots.Num(); i++)
	{

		if (QuickSlots[i] == nullptr)
		{
			UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
			NewWeapon->InitItem(WeaponTable, WeaponID);
			QuickSlots[i] = NewWeapon;

			// 새로 만든 서브오브젝트를 Replicated 등록
			AddReplicatedSubObject(NewWeapon);

			ClientNotifyItemRegistered(i, WeaponID, EItemType::Weapon);

			return true;

		}
	}

	return false;
}



bool UPlayerQuickSlotComponent::RegisterArmorToEmptySlot(FName ArmorId)
{
	if (ArmorTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] ArmorTable 자산이 바인딩되지 않았습니다."));
		return false;
	}

	for (int i = 0; i < QuickSlots.Num(); i++)
	{

		if (QuickSlots[i] == nullptr)
		{
			UArmorItem* NewArmor = NewObject<UArmorItem>(this);
			NewArmor->InitItem(ArmorTable, ArmorId);
			QuickSlots[i] = NewArmor;

			// 새로 만든 서브오브젝트를 Replicated 등록
			AddReplicatedSubObject(NewArmor);

			ClientNotifyItemRegistered(i, ArmorId, EItemType::Armor);

			return true;

		}
	}

	return false;
}

bool UPlayerQuickSlotComponent::RegisterResourceToEmptySlot(FName ResourceId, int32 Quantity)
{
	if (ResourceTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] ResourceTable 자산이 바인딩되지 않았습니다."));
		return false;
	}

	for (int i = 0; i < QuickSlots.Num(); i++)
	{

		if (QuickSlots[i] == nullptr)
		{
			UResourceItem* NewResource = NewObject<UResourceItem>(this);
			NewResource->InitItem(ResourceTable, ResourceId);
			QuickSlots[i] = NewResource;

			// 새로 만든 서브오브젝트를 Replicated 등록
			AddReplicatedSubObject(NewResource);

			ClientNotifyItemRegistered(i, ResourceId, EItemType::Resource, Quantity);

			return true;

		}
	}

	return false;
}

bool UPlayerQuickSlotComponent::RegisterPotionToEmptySlot(FName PotionId, int32 Quantity)
{
	if (PotionTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] PotionTable 자산이 바인딩되지 않았습니다."));
		return false;
	}

	for (int i = 0; i < QuickSlots.Num(); i++)
	{

		if (QuickSlots[i] == nullptr)
		{
			UPotionItem* NewPotion = NewObject<UPotionItem>(this);
			NewPotion->InitItem(PotionTable, PotionId);
			QuickSlots[i] = NewPotion;

			// 새로 만든 서브오브젝트를 Replicated 등록
			AddReplicatedSubObject(NewPotion);

			ClientNotifyItemRegistered(i, PotionId, EItemType::Potion, Quantity);

			return true;

		}
	}

	return false;
}

void UPlayerQuickSlotComponent::ExecuteSlotAction(int32 SlotIndex)
{
	// 널 포인터 접근을 차단
	if (!QuickSlots[SlotIndex]) return;

	switch (QuickSlots[SlotIndex]->GetItemType())
	{
	case (EItemType::Weapon):
	{
		ServerEquipWeapon(QuickSlots[SlotIndex]->GetItemID());

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

void UPlayerQuickSlotComponent::RemoveSlotItem(int32 SlotIndex)
{
	ServerRemoveSlotItem(SlotIndex);
}

void UPlayerQuickSlotComponent::ClientNotifySlotItemRemoved_Implementation(int32 SlotIndex)
{
	if (CachedQuickSlotWidget)
	{
		CachedQuickSlotWidget->RemoveItemSlot(SlotIndex);
	}
}

void UPlayerQuickSlotComponent::ServerRemoveSlotItem_Implementation(int32 SlotIndex)
{
	if (!QuickSlots[SlotIndex]) return;

	if (QuickSlots[SlotIndex]->GetItemType() == EItemType::Weapon)
	{
		EquipmentComponent->UpdateWeaponSlot(QuickSlots[SlotIndex]->GetItemID());
	}
	RemoveReplicatedSubObject(QuickSlots[SlotIndex]);

	// 가비지 컬렉터에 등록
	// TArray의 Remove는 사용금지
	UObject* TargetObject = QuickSlots[SlotIndex];
	if (TargetObject)
	{
		TargetObject->MarkAsGarbage();
	}

	
	QuickSlots[SlotIndex] = nullptr;

	ClientNotifySlotItemRemoved(SlotIndex);
}

void UPlayerQuickSlotComponent::ServerEquipWeapon_Implementation(FName WeaponId)
{
	if (OwnerCharacter->HasAuthority())
	{
		EquipmentComponent->UpdateWeaponSlot(WeaponId);

		OwnerCharacter->MulticastPlayEquipWeaponMontage();
	}
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

void UPlayerQuickSlotComponent::RegisterWidgetReference(UPlayerQuickSlotWidget* WidgetRef)
{
	if (WidgetRef == nullptr) 
	{ 
		return;
	}

	CachedQuickSlotWidget = WidgetRef;
}

bool UPlayerQuickSlotComponent::DropItem(int32 SlotNum, FVector DropLocation)
{
	UItemInstance* TargetItem = QuickSlots[SlotNum];

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
void UPlayerQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	if (QuickSlots.Num() == 0)
	{
		QuickSlots.SetNum(MaxSlotCount);
	}
	OwnerCharacter = Cast<APlayerCharacter>(GetOwner());

	EquipmentComponent = OwnerCharacter->GetComponentByClass<UPlayerEquipmentComponent>();
}

// Called every frame
void UPlayerQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

