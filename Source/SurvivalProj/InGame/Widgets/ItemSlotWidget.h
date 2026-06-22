// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "Input/Reply.h"
#include "Layout/Geometry.h"
#include "Input/Events.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot")
	int32 SlotIndex = 0;

	FName ItemId = NAME_None;

	void SlotUpdate(FItemSlotData SlotData);
	
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantityText;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	/*virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;*/

	UPROPERTY(EditDefaultsOnly, Category = "Slot|Visual")
	TSubclassOf<UUserWidget> DragVisualClass;
};
