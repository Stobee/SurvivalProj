// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerInventoryWidget.h"
#include "SurvivalProj/InGame/Components/PlayerQuickSlotComponent.h"


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

			QuickSlotComp->OnWidgetReferenceRegistered.AddDynamic(QuickSlotComp, &UPlayerQuickSlotComponent::RegisterWidgetReference);

			QuickSlotComp->OnWidgetReferenceRegistered.Broadcast(NewQuickUI);
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

			//UPlayerQuickSlotComponent* QuickSlotComp = PlayerPawn->GetComponentByClass<UPlayerQuickSlotComponent>();
			//if (!QuickSlotComp) return;

			//QuickSlotComp->OnWidgetReferenceRegistered.AddDynamic(QuickSlotComp, &UPlayerQuickSlotComponent::RegisterWidgetReference);

			//QuickSlotComp->OnWidgetReferenceRegistered.Broadcast(NewInventoryUI);
		}
	}
}

/*UPlayerQuickSlotWidget* AInGameHUD::GetPlayerQuickSlotWidgetRef() const
{
	if (CachedQuickSlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CachedQuickSlotWidget is nullptr. Return is nullptr."));
		return nullptr;
	}
	return CachedQuickSlotWidget;
}*/
