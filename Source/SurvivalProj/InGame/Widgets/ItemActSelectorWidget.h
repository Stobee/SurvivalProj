// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "ItemActSelectorWidget.generated.h"

class UButton;
class UTextBlock;
class APlayerCharacter;
class UItemSlotWidget;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UItemActSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	UFUNCTION(BlueprintCallable)
	void MoveToOtherComponent();

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(UItemSlotWidget* SlotWidget);

	UFUNCTION(BlueprintCallable)
	void UseItem();

	UFUNCTION(BlueprintCallable)
	void DropItem();

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MoveItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MoveItemButtonText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> UseItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> UseItemButtonText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DropItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DropItemButtonText;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	FName ItemID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	int32 ItemSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	int32 ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	UItemSlotWidget* OwningSlotWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	UUserWidget* ParentWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
	bool bTargetIsQuickSlot = false;


	

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
