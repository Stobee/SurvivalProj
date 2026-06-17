// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "Net/UnrealNetwork.h"



void UWeaponItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponItem, MaxDuravility);
	DOREPLIFETIME(UWeaponItem, CurrentDuravility);
	DOREPLIFETIME(UWeaponItem, AttackPoint);
	DOREPLIFETIME(UWeaponItem, EnhencementLevel);
	DOREPLIFETIME(UWeaponItem, WeaponType);
}

void UWeaponItem::InitItem(UDataTable* DataTable, FName ID)
{
	if (DataTable != nullptr && ID.IsValid())
	{
		Super::InitItem(DataTable, ID);
		ItemID = ID;
		ItemRow = DataTable->FindRow<FWeaponItemStruct>(ID, TEXT("WeaponItemInit"));

		ItemName = ItemRow->ItemName;
		AttackPoint = ItemRow->BaseAttackDamage;
		MaxDuravility = ItemRow->MaxDurability;

		CurrentDuravility = MaxDuravility;
		ItemType = EItemType::Weapon;
		WeaponType = ItemRow->WeaponType;
	}
	
}
