// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerQuickSlotWidget.generated.h"

class UCanvasPanel;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UPlayerQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> QuickSlotCanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> QuickSlotGrid;

	virtual void NativeConstruct() override;
};
