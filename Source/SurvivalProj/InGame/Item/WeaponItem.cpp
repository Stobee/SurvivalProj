// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "SurvivalProj/Data/Enums/EItemType.h"



void UWeaponItem::InitItem()
{
	Super::InitItem();

	if (ItemDataTable != nullptr && ItemID.IsValid())
	{
		ItemRow = ItemDataTable->FindRow<FWeaponItemStruct>(ItemID, TEXT("WeaponItemInit"));

		ItemName = ItemRow->ItemName;
		AttackPoint = ItemRow->BaseAttackDamage;
		MaxDuravility = ItemRow->MaxDurability;

		CurrentDuravility = MaxDuravility;
		ItemType = EItemType::Weapon;
	}
	
}
