// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EArmorType.generated.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EArmorType : uint8
{
	None UMETA(DisplayName = "None"),
	Helmet UMETA(DisplayName = "Helmet"),
	Top UMETA(DisplayName = "Top"),
	Bottom UMETA(DisplayName = "Bottom"),
	Boots UMETA(DisplayName = "Boots"),

};
