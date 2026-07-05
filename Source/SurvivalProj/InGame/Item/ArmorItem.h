// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "SurvivalProj/Data/DataTableStructs/ArmorItemStruct.h"
#include "ArmorItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UArmorItem : public UItemInstance
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	float GetArmorDuravility() const { return CurrentDuravility; }

	float GetArmorDP() const { return DefencePoint; }

	float GetArmorEnhencementLevel() const { return EnhencementLevel; }

	virtual void InitItem(UDataTable* DataTable, FName ID, int32 ItemQuantity = 1) override;

protected:

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	float MaxDuravility = 100.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	float CurrentDuravility = 100.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	float DefencePoint = 0.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	int32 EnhencementLevel = 0;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	EArmorType ArmorType = EArmorType::None;

	FArmorItemStruct* ItemRow = nullptr;
};
