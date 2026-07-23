// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "SurvivalProj/InGame/Widgets/PlayerInventoryWidget.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "Components/ActorComponent.h"
#include "PlayerInventoryComponent.generated.h"

class APlayerCharacter;
class AInGamePlayerController;
class UPlayerEquipmentComponent;
class UCharacterStatComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryWidgetReferenceRegistered, UPlayerInventoryWidget*, WidgetRef);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuickSlotWidgetReferenceRegistered, UPlayerQuickSlotWidget*, WidgetRef);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UPlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void ClientNotifyItemRegistered(int32 SlotIndex, FName Id, EItemType Type, int32 Quantity = 1);

	bool RegisterWeaponToEmptySlot(const FItemSlotData& ItemPacket, bool bIsQuickSlot = false);

	bool RegisterArmorToEmptySlot(const FItemSlotData& ItemPacket, bool bIsQuickSlot = false);

	bool RegisterResourceToEmptySlot(const FItemSlotData& ItemPacket, bool bIsQuickSlot = false);

	bool RegisterPotionToEmptySlot(const FItemSlotData& ItemPacket, bool bIsQuickSlot = false);
	
	void RemoveSlotItem(int32 SlotIndex);

	int32 GetInventorySize() { return MaxInventorySlotCount; }

	UFUNCTION(Server, Reliable)
	void ServerRemoveSlotItem(int32 SlotIndex);

	UFUNCTION(Client, Reliable)
	void ClientNotifySlotItemRemoved(int32 SlotIndex);

	bool bIsInventorySlotFull();

	// Äü ½½·ÔÀÌ ²Ë Ã¡´ÂÁö È®ÀÎ
	bool bIsQuickSlotFull();

	// ÇÃ·¹ÀÌ¾î°¡ Æ®¸®°ÅÇÏ¿© À§Á¬ Visible Á¶Á¤
	void VisibleInventoryWidget();

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnInventoryWidgetReferenceRegistered OnInventoryWidgetReferenceRegistered;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnQuickSlotWidgetReferenceRegistered OnQuickSlotWidgetReferenceRegistered;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterInventoryWidgetReference(UPlayerInventoryWidget* WidgetRef);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterQuickSlotWidgetReference(UPlayerQuickSlotWidget* WidgetRef);

	void UseItem(int32 SlotNum);

	UFUNCTION(Server, Reliable)
	void ServerEquipWeapon(FName WeaponId);

	bool DropItem(int32 SlotNum, FVector DropLocation);
	 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	UPlayerInventoryWidget* CachedInventoryWidget = nullptr;

	UPROPERTY()
	UPlayerQuickSlotWidget* CachedQuickSlotWidget = nullptr;

	UPROPERTY()
	AInGamePlayerController* CachedPlayerController = nullptr;

	// Origin Of Inventory & QuickSlot
	UPROPERTY(Replicated)
	TArray<UItemInstance*> InventorySlots;

	int32 MaxInventorySlotCount = 32;

	// Äü½½·ÔÀº MaxInventorySlotCount ÀÎµ¦½º ºÎÅÍ
	int32 MaxQuickSlotCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> WeaponTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> ArmorTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> ResourceTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> PotionTable = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APlayerCharacter> OwnerCharacter;

	UPROPERTY(Transient)
	TObjectPtr<UPlayerEquipmentComponent> EquipmentComponent;

	UPROPERTY(Transient)
	TObjectPtr<UCharacterStatComponent> StatComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
