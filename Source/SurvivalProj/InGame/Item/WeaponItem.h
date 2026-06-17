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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	float GetWeaponDuravility() const { return CurrentDuravility; }

	float GetWeaponAP() const { return AttackPoint; }

	virtual void InitItem(UDataTable* DataTable, FName ID) override;

protected:
	
	UPROPERTY(Replicated, VisibleAnywhere, Category = "WeaponState")
	float MaxDuravility = 100.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "WeaponState")
	float CurrentDuravility = 100.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "WeaponState")
	float AttackPoint = 0.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "WeaponState")
	int32 EnhencementLevel = 0;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "WeaponState")
	EWeaponEquipState WeaponType = EWeaponEquipState::OneHanded;

	FWeaponItemStruct* ItemRow = nullptr;
};
