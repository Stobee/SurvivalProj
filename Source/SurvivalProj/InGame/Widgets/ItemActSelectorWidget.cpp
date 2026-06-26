// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActSelectorWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/Widgets/ItemSlotWidget.h"


void UItemActSelectorWidget::MoveToOtherComponent(int32 SlotNum, FName ItemId, EItemType SlotItemType, bool bTargetIsQuickSlot)
{
	if (ItemId == NAME_None) return;

	if (PlayerRef)
	{
		PlayerRef->MoveItem(SlotNum, ItemId, SlotItemType, bTargetIsQuickSlot);
	}
}

// 슬롯 위젯에서 해당 슬롯의 부모 가져와야함
void UItemActSelectorWidget::SetItemInfo(UItemSlotWidget* SlotWidget)
{
	if (SlotWidget)
	{
		OwningSlotWidget = SlotWidget;
		ItemID = SlotWidget->ItemId;
		ItemSlotIndex = SlotWidget->SlotIndex;
		ItemType = SlotWidget->ItemType;
	}
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
