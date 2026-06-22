// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemActSelectorWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UItemActSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

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

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
