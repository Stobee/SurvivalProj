// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "InGamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AInGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	float GetMaxHp() const { return MaxHp; }
	
	float GetCurrentHp() const { return CurrentHp; }

	float GetAttackPoint() const { return AttackPoint; }

	float GetDefencePoint() const { return DefencePoint; }

	TArray<UItemInstance*> GetInventoryData() const { return InventoryData; }

	TArray<UItemInstance*> GetQuickSlotData() const { return QuickSlotData; }
	
protected:

	UPROPERTY()
	float MaxHp = 0.0f;

	UPROPERTY()
	float CurrentHp = 0.0f;

	UPROPERTY()
	float AttackPoint = 0.0f;

	UPROPERTY()
	float DefencePoint = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UItemInstance*> InventoryData;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UItemInstance*> QuickSlotData;



};
