// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "Components/ActorComponent.h"
#include "PlayerInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UPlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventoryComponent();

	// [핵심 포트] 기획자가 만든 BP_RedPotion 같은 블루프린트 클래스 타입을 인자로 안전하게 수집
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemFromClass(TSubclassOf<UItemInstance> ItemBlueprintClass, int32 Amount);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
