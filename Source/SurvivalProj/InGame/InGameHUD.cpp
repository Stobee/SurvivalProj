// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerInventoryWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerHpWidget.h"
#include "SurvivalProj/InGame/Widgets/BossHpWidget.h"
#include "SurvivalProj/InGame/Components/CharacterStatComponent.h"
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

			UPlayerInventoryComponent* InventoryComp = PlayerPawn->GetComponentByClass<UPlayerInventoryComponent>();
			if (!InventoryComp) return;

			InventoryComp->OnQuickSlotWidgetReferenceRegistered.AddDynamic(InventoryComp, &UPlayerInventoryComponent::RegisterQuickSlotWidgetReference);

			InventoryComp->OnQuickSlotWidgetReferenceRegistered.Broadcast(NewQuickUI);
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

			InventoryComp->OnInventoryWidgetReferenceRegistered.AddDynamic(InventoryComp, &UPlayerInventoryComponent::RegisterInventoryWidgetReference);

			InventoryComp->OnInventoryWidgetReferenceRegistered.Broadcast(NewInventoryUI);
		}
	}

	// Create PlayerHPWidget
	if (PlayerHPWidgetClass != nullptr)
	{
		UPlayerHpWidget* NewHpUI = CreateWidget<UPlayerHpWidget>(PC, PlayerHPWidgetClass);
		if (NewHpUI != nullptr)
		{

			NewHpUI->AddToViewport();

			NewHpUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			UCharacterStatComponent* StatComp = PlayerPawn->GetComponentByClass<UCharacterStatComponent>();
			if (!StatComp) return;

			StatComp->OnPlayerHpWidgetReferenceRegistered.AddDynamic(StatComp, &UCharacterStatComponent::RegisterWidgetReference);

			StatComp->OnPlayerHpWidgetReferenceRegistered.Broadcast(NewHpUI);
		}
	}
}

