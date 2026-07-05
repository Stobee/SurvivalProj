// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "SurvivalProj/Data/DataTableStructs/ResourceItemStruct.h"
#include "ResourceItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UResourceItem : public UItemInstance
{
	GENERATED_BODY()
	
public:

	virtual void InitItem(UDataTable* DataTable, FName ID, int32 ItemQuantity = 1) override;

protected:

	FResourceItemStruct* ItemRow = nullptr;
};
