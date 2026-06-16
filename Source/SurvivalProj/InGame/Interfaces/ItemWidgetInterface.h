// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "ItemWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALPROJ_API IItemWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	//virtual void UpdateItemSlot(int32 IndexNum, const FItemSlotData& ItemSlotData) = 0;
};
