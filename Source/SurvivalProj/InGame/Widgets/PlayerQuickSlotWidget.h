// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalProj/InGame/Interfaces/ItemWidgetInterface.h"
#include "PlayerQuickSlotWidget.generated.h"

class UCanvasPanel;
class UUniformGridPanel;
class UItemSlotWidget;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UPlayerQuickSlotWidget : public UUserWidget, public IItemWidgetInterface
{
	GENERATED_BODY()

public:

	void UpdateItemSlot(int32 IndexNum, const FItemSlotData& ItemSlotData);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> QuickSlotCanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> QuickSlotGrid;

	UPROPERTY(EditDefaultsOnly, Category = "UI Config")
	TSubclassOf<UItemSlotWidget> SlotWidget;

	UPROPERTY()
	TArray<TObjectPtr<UItemSlotWidget>> CachedSlots;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
