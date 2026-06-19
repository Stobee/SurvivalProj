// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UPlayerQuickSlotWidget;
class UPlayerInventoryWidget;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI Config")
	TSubclassOf<UPlayerQuickSlotWidget> QuickSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI Config")
	TSubclassOf<UPlayerInventoryWidget> InventoryWidgetClass;

	virtual void BeginPlay() override;

private:

	//UPROPERTY()
	//TObjectPtr<UPlayerQuickSlotWidget> CachedQuickSlotWidget;

public:

	//class UPlayerQuickSlotWidget* GetPlayerQuickSlotWidgetRef() const;
	
};
