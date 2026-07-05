// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionItem.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "Net/UnrealNetwork.h"

void UPotionItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPotionItem, IncreasePoint);
	DOREPLIFETIME(UPotionItem, PotionType);
}

void UPotionItem::InitItem(UDataTable* DataTable, FName ID, int32 ItemQuantity)
{
	if (DataTable != nullptr && ID.IsValid())
	{
		Super::InitItem(DataTable, ID);
		ItemID = ID;
		ItemRow = DataTable->FindRow<FPotionItemStruct>(ID, TEXT("PotionItemInit"));

		ItemName = ItemRow->ItemName;
		IncreasePoint = ItemRow->IncreaseStatPoint;
		Quantity = ItemQuantity;
		
		
		ItemType = EItemType::Potion;
		PotionType = ItemRow->PotionType;
	}
}
