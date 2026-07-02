// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorItem.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "Net/UnrealNetwork.h"

void UArmorItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArmorItem, MaxDuravility);
	DOREPLIFETIME(UArmorItem, CurrentDuravility);
	DOREPLIFETIME(UArmorItem, DefencePoint);
	DOREPLIFETIME(UArmorItem, EnhencementLevel);
	DOREPLIFETIME(UArmorItem, ArmorType);
}

void UArmorItem::InitItem(UDataTable* DataTable, FName ID)
{
	if (DataTable != nullptr && ID.IsValid())
	{
		Super::InitItem(DataTable, ID);
		ItemID = ID;
		ItemRow = DataTable->FindRow<FArmorItemStruct>(ID, TEXT("ArmorItemInit"));

		ItemName = ItemRow->ItemName;
		DefencePoint = ItemRow->BaseDefencePoint;
		MaxDuravility = ItemRow->MaxDurability;

		CurrentDuravility = MaxDuravility;
		ItemType = EItemType::Armor;
		ArmorType = ItemRow->ArmorType;
	}
}
