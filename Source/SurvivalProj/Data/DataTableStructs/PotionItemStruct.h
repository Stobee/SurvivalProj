// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // 데이터 테이블 가동을 위한 필수 헤더 인입
#include "SurvivalProj/InGame/Item/FieldItem.h"
#include "SurvivalProj/Data/Enums/EPotionType.h"
#include "PotionItemStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FPotionItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 기획자가 에디터에서 타이핑하거나 엑셀에서 밀어 넣을 변수 전선 배치

	//아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	FText ItemName;

	//아이템 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	UTexture2D* ItemIconTexture = nullptr;

	//필드 아이템 메시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	TSubclassOf<AFieldItem> FieldPotionActor = nullptr;

	//아이템 설명 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	FText ItemDescription;

	//스탯 증가량
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	float IncreaseStatPoint;

	//아이템 형태
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	EPotionType PotionType = EPotionType::None;
};