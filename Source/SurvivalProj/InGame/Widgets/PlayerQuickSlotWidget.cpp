// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuickSlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "SurvivalProj/InGame/Widgets/ItemSlotWidget.h"
#include "PlayerInventoryWidget.h"


void UPlayerQuickSlotWidget::UpdateItemSlot(int32 IndexNum, const FItemSlotData& ItemSlotData)
{
	if (ItemSlotData.Quantity == 0 || ItemSlotData.IconTexture == nullptr) return;

	CachedSlots[IndexNum]->SlotUpdate(ItemSlotData);
}

void UPlayerQuickSlotWidget::RemoveItemSlot(int32 IndexNum)
{
	CachedSlots[IndexNum]->SlotRemove();
}


void UPlayerQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerQuickSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	QuickSlotGrid->ClearChildren();
	CachedSlots.Empty();
	if (SlotWidget)
	{
		for (size_t i = 0; i < 5; i++)
		{

			// 1. 낱개 슬롯 위젯 인스턴스 동적 생성
			UItemSlotWidget* QuickSlot = CreateWidget<UItemSlotWidget>(this, SlotWidget);
			if (QuickSlot != nullptr)
			{
				// 2. 유니폼 그리드 패널의 0행, i열 자리에 강제 각인 배치
				UUniformGridSlot* GridSlot = QuickSlotGrid->AddChildToUniformGrid(QuickSlot, 0, i);

				// 3. 내부 C++ 주소록 배열에 순서대로 적재
				CachedSlots.Add(QuickSlot);
			}
		}
	}

}
