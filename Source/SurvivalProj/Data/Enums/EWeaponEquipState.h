// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EWeaponEquipState.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EWeaponEquipState : uint8
{
	Unarmed UMETA(DisplayName = "무기 없음"),
	OneHanded UMETA(DisplayName = "한 손 무기"),
	TwoHanded UMETA(DisplayName = "두 손 무기")

};