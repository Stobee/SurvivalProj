// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "ItemWidgetStruct.generated.h"



/**
 * [핵심] USTRUCT 내부에 BlueprintType을 주입하고, FTableRowBase를 상속받아야
 * 언리얼 에디터가 이를 데이터 테이블 생성용 시트로 규격 인식함.
 */
USTRUCT(BlueprintType)
struct FItemSlotData
{
	GENERATED_BODY()

	
	UPROPERTY(BlueprintReadOnly)
	FName ItemId = NAME_None;

	UPROPERTY(BlueprintReadOnly)
	EItemType ItemType = EItemType::None;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> IconTexture = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SlotNumber = 0;

	UPROPERTY(BlueprintReadOnly)
	float CurrentDuravility = 100.0f;

	UPROPERTY(BlueprintReadOnly)
	int32 EnhencementLevel = 0;

	UPROPERTY(BlueprintReadOnly)
	float AttackPoint = 0.0f;
};
