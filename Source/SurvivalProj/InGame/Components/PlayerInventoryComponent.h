// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "SurvivalProj/InGame/Widgets/PlayerInventoryWidget.h"
#include "Components/ActorComponent.h"
#include "PlayerInventoryComponent.generated.h"

class APlayerCharacter;
class UPlayerEquipmentComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWidgetReferenceRegistered, UPlayerInventoryWidget*, WidgetRef);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UPlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void ServerRegisterWeaponToEmptySlot(FName WeaponID);

	UFUNCTION(Client, Reliable)
	void ClientNotifyWeaponRegistered(int32 SlotIndex, FName Id);

	void RegisterWeaponToEmptySlot(FName WeaponId);

	void RegisterArmorToEmptySlot(FName ArmorId);

	void RegisterResourceToEmptySlot(FName ResourceId, int32 Quantity);

	void RegisterPotionToEmptySlot(FName PotionId, int32 Quantity);
	
	bool bIsInventorySlotFull();

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnWidgetReferenceRegistered OnWidgetReferenceRegistered;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterWidgetReference(UPlayerInventoryWidget* WidgetRef);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	UPlayerInventoryWidget* CachedQuickSlotWidget = nullptr;

	UPROPERTY(Replicated)
	TArray<UItemInstance*> InventorySlots;

	int32 MaxSlotCount = 32;

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
