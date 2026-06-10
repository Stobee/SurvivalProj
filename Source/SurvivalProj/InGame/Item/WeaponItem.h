// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UWeaponItem : public UItemInstance
{
	GENERATED_BODY()

public:
	float GetWeaponDuravility() const { return CurrentDuravility; }

	float GetWeaponAP() const { return AttackPoint; }

	virtual void InitItem(UDataTable* DataTable, FName ID) override;

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "WeaponState")
	float MaxDuravility = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "WeaponState")
	float CurrentDuravility = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "WeaponState")
	float AttackPoint = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "WeaponState")
	int32 EnhencementLevel = 0;

	FWeaponItemStruct* ItemRow = nullptr;
};
