// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInstance.h"
#include "Net/UnrealNetwork.h"

void UItemInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UItemInstance, ItemID);
	DOREPLIFETIME(UItemInstance, Quantity);
	DOREPLIFETIME(UItemInstance, ItemType);
}

void UItemInstance::InitItem(UDataTable* DataTable, FName ID)
{

}

void UItemInstance::UseItem(ACharacter* UserCharacter)
{
}

void UItemInstance::BeginDestroy()
{
	Super::BeginDestroy();

	// 내 상위 Outer(소유자)가 퀵슬롯 컴포넌트인 것이 수사 입증된다면
	if (UActorComponent* MyOwnerComp = Cast<UActorComponent>(GetOuter()))
	{
		// 내가 메모리에서 파괴되는 프레임에 부모의 복제 리스트에서 나를 자동으로 지운다!
		MyOwnerComp->RemoveReplicatedSubObject(this);
	}
}
