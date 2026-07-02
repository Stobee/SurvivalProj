// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "PlayerEquipmentComponent.generated.h"

class UWeaponItem;
class APlayerCharacter;
class AEquipWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UPlayerEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerEquipmentComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateWeaponSlot(FName WeaponId);

	void ChangeStats(EItemType ItemType, bool bIsAdd);

	FVector GetEquipWeaponActorSocketLocation();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	TObjectPtr<UWeaponItem> WeaponSlot = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APlayerCharacter> OwnerCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> WeaponTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> ArmorTable = nullptr;

	UPROPERTY(Transient)
	TSubclassOf<AEquipWeapon> EquipWeaponClass = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<AEquipWeapon> EquipWeaponActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FName WeaponSocketName = NAME_None;

	UFUNCTION()
	void AttachWeapon(FName WeaponId);

	UFUNCTION()
	void DettachWeapon();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
