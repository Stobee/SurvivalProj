// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "ItemActSelectorWidget.generated.h"

class UButton;
class UTextBlock;
class APlayerCharacter;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UItemActSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	UFUNCTION()
	void MoveToOtherComponent(int32 SlotNum, FName ItemId, EItemType SlotItemType, bool bTargetIsQuickSlot);

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(int32 SlotIndex, FName ItemId, EItemType SlotItemType);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 ItemSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemType ItemType;



	

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
