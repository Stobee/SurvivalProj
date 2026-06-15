// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UItemSlotWidget::SlotUpdate(FItemSlotData SlotData)
{
	ItemImage->SetBrushFromTexture(SlotData.IconTexture);
	// int를 text로 바꿔서 인입.
	ItemQuantityText->SetText(FText::AsNumber(SlotData.Quantity));
	ItemId = SlotData.ItemId;
	ItemImage->SetVisibility(ESlateVisibility::Visible);
	ItemQuantityText->SetVisibility(ESlateVisibility::Visible);

}

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		ItemQuantityText->SetVisibility(ESlateVisibility::Hidden);
	}
}
