// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotify.h"
#include "SurvivalProj/InGame/Interfaces/AttackNotifyInterface.h"

// 정상 작동 확인 후 무기 전용 노티파이 추가
void UAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    
    IAttackNotifyInterface* CombatActor = Cast<IAttackNotifyInterface>(MeshComp->GetOwner());
    if (CombatActor != nullptr)
    {
       CombatActor->ExecuteShortAttackTrace();

    }
    
}
