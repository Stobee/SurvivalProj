// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPotionType.generated.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EPotionType : uint8
{
	None UMETA(DisplayName = "None"),
	HP UMETA(DisplayName = "HP_Potion"),
	MP UMETA(DisplayName = "MP_Potion"),
	AP UMETA(DisplayName = "AP_Potion"),
	Stamina UMETA(DisplayName = "Stamina_Potion"),

};