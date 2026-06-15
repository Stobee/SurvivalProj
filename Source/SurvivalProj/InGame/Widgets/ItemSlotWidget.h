// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "ItemSlotWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FName ItemId = NAME_None;

	void SlotUpdate(FItemSlotData SlotData);
	
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantityText;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
