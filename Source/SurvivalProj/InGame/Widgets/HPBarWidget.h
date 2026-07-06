// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
	
	void HPBarUpdate(float MaxHp, float CurrentHp);
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPProgressBar;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
