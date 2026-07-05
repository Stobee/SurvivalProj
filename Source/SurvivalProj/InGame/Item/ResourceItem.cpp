// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceItem.h"

void UResourceItem::InitItem(UDataTable* DataTable, FName ID, int32 ItemQuantity)
{
	if (DataTable != nullptr && ID.IsValid())
	{
		Super::InitItem(DataTable, ID);
		ItemID = ID;
		ItemRow = DataTable->FindRow<FResourceItemStruct>(ID, TEXT("ResourceItemInit"));

		ItemName = ItemRow->ItemName;
		ItemType = EItemType::Resource;
		Quantity = ItemQuantity;

	}
}
