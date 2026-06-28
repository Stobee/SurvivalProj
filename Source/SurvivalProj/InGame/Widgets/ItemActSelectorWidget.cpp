// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActSelectorWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"
#include "SurvivalProj/InGame/Widgets/ItemSlotWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"


void UItemActSelectorWidget::MoveToOtherComponent(int32 SlotNum, FName ItemId, EItemType SlotItemType, bool bTargetIsQuickSlot)
{
	if (ItemId == NAME_None) return;

	if (PlayerRef)
	{
		PlayerRef->MoveItem(SlotNum, ItemId, SlotItemType, bTargetIsQuickSlot);
	}
}

void UItemActSelectorWidget::SetItemInfo(UItemSlotWidget* SlotWidget)
{
	if (SlotWidget)
	{
		OwningSlotWidget = SlotWidget;
		ItemID = SlotWidget->ItemId;
		ItemSlotIndex = SlotWidget->SlotIndex;
		ItemType = SlotWidget->ItemType;

		UPlayerQuickSlotWidget* QuickSlot = Cast<UPlayerQuickSlotWidget>(SlotWidget->GetOuter());

		// 캐스팅 성공 여부에 따라 분기
		if (QuickSlot)
		{
			bTargetIsQuickSlot = false;
		}
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
