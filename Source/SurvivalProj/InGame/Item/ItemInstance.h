// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	// 데이터 테이블 수색용 고유 해시 키
	FName GetItemID() const { return ItemID; }
	int32 GetQuantity() const { return Quantity; }

	void SetItemID(FName InID) { ItemID = InID; }
	void AddQuantity(int32 Amount) { Quantity += Amount; }

	// 자식 아이템(포션, 장비)들이 독단적으로 재정의할 연산 가교
	virtual void UseItem(class ACharacter* UserCharacter);

	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "ItemState")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, Category = "ItemState")
	int32 Quantity;
};
