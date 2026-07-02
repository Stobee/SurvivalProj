// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerInventoryWidget.h"
#include "SurvivalProj/InGame/Components/PlayerQuickSlotComponent.h"
#include "SurvivalProj/InGame/Components/PlayerInventoryComponent.h"


void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	if (PC == nullptr) return;

	if (PC->IsLocalController() == false) return;

	APawn* PlayerPawn = PC->GetPawn();
	if (!PlayerPawn) return;
	
	// Create QuickSlotWidget
	if (QuickSlotWidgetClass != nullptr)
	{
		
		UPlayerQuickSlotWidget* NewQuickUI = CreateWidget<UPlayerQuickSlotWidget>(PC, QuickSlotWidgetClass);
		if (NewQuickUI != nullptr)
		{
			
			NewQuickUI->AddToViewport();

			UPlayerQuickSlotComponent* QuickSlotComp = PlayerPawn->GetComponentByClass<UPlayerQuickSlotComponent>();
			if (!QuickSlotComp) return;

			QuickSlotComp->OnQuickSlotWidgetReferenceRegistered.AddDynamic(QuickSlotComp, &UPlayerQuickSlotComponent::RegisterWidgetReference);

			QuickSlotComp->OnQuickSlotWidgetReferenceRegistered.Broadcast(NewQuickUI);
		}
	}

	// Create InventoryWidget
	if (InventoryWidgetClass != nullptr)
	{
		UPlayerInventoryWidget* NewInventoryUI = CreateWidget<UPlayerInventoryWidget>(PC, InventoryWidgetClass);
		if (NewInventoryUI != nullptr)
		{

			NewInventoryUI->AddToViewport();

			NewInventoryUI->SetVisibility(ESlateVisibility::Collapsed);

			UPlayerInventoryComponent* InventoryComp = PlayerPawn->GetComponentByClass<UPlayerInventoryComponent>();
			if (!InventoryComp) return;

			InventoryComp->OnInventoryWidgetReferenceRegistered.AddDynamic(InventoryComp, &UPlayerInventoryComponent::RegisterWidgetReference);

			InventoryComp->OnInventoryWidgetReferenceRegistered.Broadcast(NewInventoryUI);
		}
	}
}

