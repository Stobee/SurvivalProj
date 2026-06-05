// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "PlayerQuickSlotComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UPlayerQuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerQuickSlotComponent();

	void RegisterItemToSlot(int32 SlotIndex, UItemInstance* ItemToLink);

	void ExecuteSlotAction(int32 SlotIndex);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UItemInstance*> QuickSlots;

	int32 MaxSlotCount = 5;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
