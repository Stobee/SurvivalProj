// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActSelectorWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/Widgets/ItemSlotWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"



void UItemActSelectorWidget::MoveToOtherComponent()
{
	if (ItemData.ItemId == NAME_None) return;

	if (PlayerRef)
	{
		PlayerRef->MoveItem(ItemData, bTargetIsQuickSlot);
	}

	RemoveFromParent();
}

void UItemActSelectorWidget::SetItemInfo(UItemSlotWidget* SlotWidget)
{
	if (SlotWidget)
	{
		OwningSlotWidget = SlotWidget;
		ItemData.ItemId = SlotWidget->ItemId;
		ItemData.SlotNumber = SlotWidget->SlotIndex;
		ItemData.ItemType = SlotWidget->ItemType;
		ItemData.Quantity = SlotWidget->ItemQuantity;
		ParentWidget = SlotWidget->ParentWidget;

		UPlayerQuickSlotWidget* QuickSlot = Cast<UPlayerQuickSlotWidget>(ParentWidget);

		// 캐스팅 성공 여부에 따라 분기
		if (QuickSlot)
		{
			bTargetIsQuickSlot = true;
		}
	}
}

void UItemActSelectorWidget::UseItem()
{
	if (ItemData.ItemId == NAME_None) return;

	PlayerRef->UseItem(ItemData.SlotNumber);

	RemoveFromParent();
}

void UItemActSelectorWidget::DropItem()
{
	if (ItemData.ItemId == NAME_None) return;

	PlayerRef->DropItem(ItemData.SlotNumber);

	RemoveFromParent();
}

void UItemActSelectorWidget::NativeConstruct()
{
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn) return;

	PlayerRef = Cast<APlayerCharacter>(PlayerPawn);

	
}

void UItemActSelectorWidget::NativeOnInitialized()
{
}
