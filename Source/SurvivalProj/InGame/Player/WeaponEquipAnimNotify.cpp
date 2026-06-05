// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEquipAnimNotify.h"
#include "SurvivalProj/InGame/Interfaces/CharacterEquipInterface.h"

void UWeaponEquipAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    ICharacterEquipInterface* Character = Cast<ICharacterEquipInterface>(MeshComp->GetOwner());
    if (Character != nullptr)
    {
        Character->SetWeaponVisible();

    }
}
