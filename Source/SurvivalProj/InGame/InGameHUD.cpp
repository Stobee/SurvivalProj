// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"
#include "SurvivalProj/InGame/Interfaces/ItemWidgetInterface.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	if (PC == nullptr) return;

	if (PC->IsLocalController() == false) return;
	
	if (QuickSlotWidgetClass != nullptr)
	{
		
		UPlayerQuickSlotWidget* NewQuickUI = CreateWidget<UPlayerQuickSlotWidget>(PC, QuickSlotWidgetClass);
		if (NewQuickUI != nullptr)
		{
			
			NewQuickUI->AddToViewport();

			
			CachedQuickSlotWidget = NewQuickUI;
		}
	}
}

IItemWidgetInterface* AInGameHUD::GetPlayerQuickSlotInterface() const
{
	if (CachedQuickSlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CachedQuickSlotWidget is nullptr. Return is nullptr."));
		return nullptr;
	}
	return Cast<IItemWidgetInterface>(CachedQuickSlotWidget);
}
