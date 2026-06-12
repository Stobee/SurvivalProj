// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


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
	}
}
