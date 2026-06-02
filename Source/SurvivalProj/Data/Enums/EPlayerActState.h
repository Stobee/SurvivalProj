// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPlayerActState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerActState : uint8
{
	Movable UMETA(DisplayName = "이동 가능"),
	Attack UMETA(DisplayName = "공격 중"),
	
};