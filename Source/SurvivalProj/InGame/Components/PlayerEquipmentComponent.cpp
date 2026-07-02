// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEquipmentComponent.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalProj/InGame/Item/WeaponItem.h"
#include "SurvivalProj/Data/DataTableStructs/WeaponItemStruct.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"



// Sets default values for this component's properties
UPlayerEquipmentComponent::UPlayerEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;

	// ...
}

void UPlayerEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UPlayerEquipmentComponent, WeaponSlot, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UPlayerEquipmentComponent, EquipWeaponActor, COND_OwnerOnly);
}

// Add Or Delete WeaponSlot
void UPlayerEquipmentComponent::UpdateWeaponSlot(FName WeaponId)
{
	
	if (WeaponTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[테이블 파열] WeaponTable 자산이 바인딩되지 않았습니다."));
		return;
	}

	// Check WeaponSlot is Empty 
	if (WeaponSlot)
	{
		if (WeaponSlot->GetItemID() == WeaponId)
		{
			// Clear WeaponSlot
			RemoveReplicatedSubObject(WeaponSlot);
			ChangeStats(EItemType::Weapon, false);
			WeaponSlot = nullptr;
			DettachWeapon();

			OwnerCharacter->WeaponEquipState = EWeaponEquipState::Unarmed;
		}
		else
		{
			// Clear WeaponSlot and Register
			RemoveReplicatedSubObject(WeaponSlot);
			ChangeStats(EItemType::Weapon, false);
			WeaponSlot = nullptr;
			DettachWeapon();

			UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
			NewWeapon->InitItem(WeaponTable, WeaponId);
			WeaponSlot = NewWeapon;
			ChangeStats(EItemType::Weapon, true);
			AddReplicatedSubObject(WeaponSlot);

			AttachWeapon(WeaponId);
		}
	}
	// Register Weapon
	else
	{
		
		UWeaponItem* NewWeapon = NewObject<UWeaponItem>(this);
		NewWeapon->InitItem(WeaponTable, WeaponId);
		WeaponSlot = NewWeapon;
		ChangeStats(EItemType::Weapon, true);
		AddReplicatedSubObject(WeaponSlot);

		AttachWeapon(WeaponId);
	}
}

// Update PlayerCharacter's Stats
void UPlayerEquipmentComponent::ChangeStats(EItemType ItemType, bool bIsAdd)
{
	if (!OwnerCharacter) return;

	switch (ItemType)
	{
	case (EItemType::Weapon) : 
	{

		break;
	}
	case (EItemType::Armor) :
	{
		break;
	}
	}
}

FVector UPlayerEquipmentComponent::GetEquipWeaponActorSocketLocation(bool bIsDifferentSocket)
{
	if (EquipWeaponActor)
	{
		FVector SocketLocation;

		if (bIsDifferentSocket)
		{
			SocketLocation = EquipWeaponActor->GetWeaponMeshComp()->GetSocketLocation(TEXT("AttackComboTrace"));
		}
		else
		{
			SocketLocation = EquipWeaponActor->GetWeaponMeshComp()->GetSocketLocation(TEXT("AttackTraceSocket"));
		}

		return SocketLocation;
	}
	return FVector(0.0f, 0.0f, 0.0f);
}


// Called when the game starts
void UPlayerEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwner());

	// ...
	
}


void UPlayerEquipmentComponent::AttachWeapon(FName WeaponId)
{
	if (OwnerCharacter == nullptr) return;

	USkeletalMeshComponent* MeshComp = OwnerCharacter->GetMesh();
	if (MeshComp == nullptr) return;

	WeaponSocketName = TEXT("S_Weapon_r");

	FTransform SpawnTransform = OwnerCharacter->GetActorTransform();

	// 스폰 파라미터 생성
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacter;
	SpawnParams.Instigator = OwnerCharacter;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FWeaponItemStruct* ItemRow = WeaponTable->FindRow<FWeaponItemStruct>(WeaponId, TEXT("WeaponEquip"));

	EquipWeaponClass = ItemRow->EquipWeaponActor;

	EquipWeaponActor = GetWorld()->SpawnActor<AEquipWeapon>(EquipWeaponClass, SpawnTransform, SpawnParams);

	if (EquipWeaponActor)
	{
		EquipWeaponActor->SetActorEnableCollision(false);

		// Attach 옵션 구조체
		FAttachmentTransformRules AttachRules(
			EAttachmentRule::KeepRelative,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false
		);

		if (WeaponSocketName != NAME_None)
		{
			EquipWeaponActor->AttachToComponent(MeshComp, AttachRules, WeaponSocketName);

			// 데이터 테이블 내 오프셋으로 변경
			EquipWeaponActor->SetActorRelativeLocation(ItemRow->WeaponSocketOffset);

			OwnerCharacter->WeaponEquipState = ItemRow->WeaponType;

		}
	}
}

void UPlayerEquipmentComponent::DettachWeapon()
{


	if (EquipWeaponActor)
	{
		// Dettach 옵션 구조체
		FDetachmentTransformRules DetachRules(
			EDetachmentRule::KeepWorld, // 소켓에서 떨어지는 순간 그 자리에 실물 좌표를 잠시 보존
			true                        // 캐릭터의 뼈대 물리 바디와 합선 충돌 피격 방지 완장
		);

		EquipWeaponActor->DetachFromActor(DetachRules);

		EquipWeaponActor->Destroy();

		EquipWeaponActor = nullptr;
	}

}

// Called every frame
void UPlayerEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

