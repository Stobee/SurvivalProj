// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "SurvivalProj/InGame/Widgets/ItemSlotWidget.h"


void UPlayerInventoryWidget::UpdateItemSlot(int32 IndexNum, const FItemSlotData& ItemSlotData)
{
	if (ItemSlotData.Quantity == 0 || ItemSlotData.IconTexture == nullptr) return;

	CachedSlots[IndexNum]->SlotUpdate(ItemSlotData);
}


void UPlayerInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InventoryGrid->ClearChildren();
	CachedSlots.Empty();
	if (SlotWidget)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{	// 1. 낱개 슬롯 위젯 인스턴스 동적 생성
				UItemSlotWidget* InventorySlot = CreateWidget<UItemSlotWidget>(this, SlotWidget);
				if (InventorySlot != nullptr)
				{
					// 2. 유니폼 그리드 패널의 0행, i열 자리에 강제 각인 배치
					UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(InventorySlot, i, j);

					// 3. 내부 C++ 주소록 배열에 순서대로 적재
					CachedSlots.Add(InventorySlot);
				}
			}
		}
	}
}
