// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UPlayerQuickSlotWidget;
class IItemWidgetInterface;

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

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<UPlayerQuickSlotWidget> CachedQuickSlotWidget;

public:

	class IItemWidgetInterface* GetPlayerQuickSlotInterface() const;
	
};
