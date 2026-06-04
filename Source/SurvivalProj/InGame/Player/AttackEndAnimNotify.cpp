// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackEndAnimNotify.h"
#include "SurvivalProj/InGame/Interfaces/AttackNotifyInterface.h"

void UAttackEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    if (MeshComp && MeshComp->GetOwner())
    {
        IAttackNotifyInterface* CombatActor = Cast<IAttackNotifyInterface>(MeshComp->GetOwner());
        if (CombatActor != nullptr)
        {
            CombatActor->SetCharacterAttackEnd();
            
        }
    }
}
