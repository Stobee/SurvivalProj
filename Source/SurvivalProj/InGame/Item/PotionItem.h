// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "SurvivalProj/Data/Enums/EPotionType.h"
#include "SurvivalProj/Data/DataTableStructs/PotionItemStruct.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UPotionItem : public UItemInstance
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	float GetIncreasePoint() const { return IncreasePoint; }

	virtual void InitItem(UDataTable* DataTable, FName ID) override;

protected:

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	float IncreasePoint = 0.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	int32 EnhencementLevel = 0;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "ArmorState")
	EPotionType PotionType = EPotionType::None;

	FPotionItemStruct* ItemRow = nullptr;
};
