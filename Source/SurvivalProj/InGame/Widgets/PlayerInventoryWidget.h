// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalProj/InGame/Interfaces/ItemWidgetInterface.h"
#include "PlayerInventoryWidget.generated.h"


class UCanvasPanel;
class UUniformGridPanel;
class UItemSlotWidget;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void UpdateItemSlot(int32 IndexNum, const FItemSlotData& ItemSlotData);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryCanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> InventoryGrid;

	UPROPERTY(EditDefaultsOnly, Category = "UI Config")
	TSubclassOf<UItemSlotWidget> SlotWidget;

	UPROPERTY()
	TArray<TObjectPtr<UItemSlotWidget>> CachedSlots;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
