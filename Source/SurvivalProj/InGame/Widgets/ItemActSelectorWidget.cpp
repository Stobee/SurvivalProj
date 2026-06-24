// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActSelectorWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"


void UItemActSelectorWidget::MoveToOtherComponent(int32 SlotNum, FName ItemId, EItemType SlotItemType, bool bTargetIsQuickSlot)
{
	if (ItemId == NAME_None) return;

	if (PlayerRef)
	{
		PlayerRef->MoveItem(SlotNum, ItemId, SlotItemType, bTargetIsQuickSlot);
	}
}

void UItemActSelectorWidget::SetItemInfo(int32 SlotIndex, FName ItemId, EItemType SlotItemType)
{
	ItemID = ItemId;
	ItemSlotIndex = SlotIndex;
	ItemType = SlotItemType;
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
