// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EItemType.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "무기"),
	Armor UMETA(DisplayName = "방어구"),
	Potion UMETA(DisplayName = "물약"),
	Resource UMETA(DisplayName = "재료"),

};
