// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // 데이터 테이블 가동을 위한 필수 헤더 인입
#include "WeaponItemStruct.generated.h"

class AEquipWeapon;

/**
 * [핵심] USTRUCT 내부에 BlueprintType을 주입하고, FTableRowBase를 상속받아야
 * 언리얼 에디터가 이를 데이터 테이블 생성용 시트로 규격 인식함.
 */
USTRUCT(BlueprintType)
struct FWeaponItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 기획자가 에디터에서 타이핑하거나 엑셀에서 밀어 넣을 변수 전선 배치

	//아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FText ItemName;

	//아이템 기본 데미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 BaseAttackDamage = 0;

	//아이템 최대 내구도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float MaxDurability = 100.f;

	//아이템 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	UTexture2D* ItemIconTexture = nullptr;

	//아이템 메시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	AEquipWeapon* EquipWeaponActor = nullptr;

	//아이템 설명 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FText ItemDescription;
};