// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "SurvivalProj/InGame/Widgets/PlayerQuickSlotWidget.h"
#include "PlayerQuickSlotComponent.generated.h"

class APlayerCharacter;
class UPlayerEquipmentComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuickSlotWidgetReferenceRegistered, UPlayerQuickSlotWidget*, WidgetRef);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UPlayerQuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerQuickSlotComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void ClientNotifyWeaponRegistered(int32 SlotIndex, FName Id);

	bool RegisterWeaponToEmptySlot(FName WeaponId);

	void RegisterArmorToEmptySlot(FName ArmorId);

	void RegisterResourceToEmptySlot(FName ResourceId, int32 Quantity);
	
	void RegisterPotionToEmptySlot(FName PotionId, int32 Quantity);

	void ExecuteSlotAction(int32 SlotIndex);

	void RemoveSlotItem(int32 SlotIndex);

	UFUNCTION(Server, Reliable)
	void ServerRemoveSlotItem(int32 SlotIndex);

	UFUNCTION(Client, Reliable)
	void ClientNotifySlotItemRemoved(int32 SlotIndex);

	UFUNCTION(Server, Reliable)
	void ServerEquipWeapon(FName WeaponId);

	// Äü ½½·ÔÀÌ ²Ë Ã¡´ÂÁö È®ÀÎ
	bool bIsQuickSlotFull();

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnQuickSlotWidgetReferenceRegistered OnQuickSlotWidgetReferenceRegistered;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterWidgetReference(UPlayerQuickSlotWidget* WidgetRef);

	bool DropItem(int32 SlotNum, FVector DropLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UPlayerQuickSlotWidget* CachedQuickSlotWidget = nullptr;

	UPROPERTY(Replicated)
	TArray<UItemInstance*> QuickSlots;

	int32 MaxSlotCount = 5;

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


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
