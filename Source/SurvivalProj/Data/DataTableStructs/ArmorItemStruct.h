// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // 데이터 테이블 가동을 위한 필수 헤더 인입
#include "SurvivalProj/InGame/Item/FieldItem.h"
#include "SurvivalProj/Data/Enums/EArmorType.h"
#include "SurvivalProj/InGame/Item/EquipArmor.h"
#include "ArmorItemStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FArmorItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 기획자가 에디터에서 타이핑하거나 엑셀에서 밀어 넣을 변수 전선 배치

	//아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	FText ItemName;

	//아이템 기본 데미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	int32 BaseDefencePoint = 0;

	//아이템 최대 내구도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	float MaxDurability = 100.0f;

	//아이템 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	UTexture2D* ItemIconTexture = nullptr;

	//장착 아이템 메시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	TSubclassOf<AEquipArmor> EquipArmorActor = nullptr;

	//필드 아이템 메시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	TSubclassOf<AFieldItem> FieldArmorActor = nullptr;

	//아이템 설명 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	FText ItemDescription;

	//아이템 형태
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	EArmorType ArmorType = EArmorType::None;

	//소켓 부착 시 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	FVector ArmorSocketOffset = FVector(0.0f, 0.0f, 0.0f);
};