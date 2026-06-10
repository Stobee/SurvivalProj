// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "SurvivalProj/Data/Enums/EItemType.h"



void UWeaponItem::InitItem(UDataTable* DataTable, FName ID)
{
	if (ItemDataTable != nullptr && ID.IsValid())
	{
		Super::InitItem(ItemDataTable, ID);
		ItemID = ID;
		ItemRow = ItemDataTable->FindRow<FWeaponItemStruct>(ID, TEXT("WeaponItemInit"));

		ItemName = ItemRow->ItemName;
		AttackPoint = ItemRow->BaseAttackDamage;
		MaxDuravility = ItemRow->MaxDurability;

		CurrentDuravility = MaxDuravility;
		ItemType = EItemType::Weapon;
	}
	
}
