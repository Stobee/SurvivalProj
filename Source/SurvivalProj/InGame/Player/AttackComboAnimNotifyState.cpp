// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComboAnimNotifyState.h"
#include "SurvivalProj/InGame/Interfaces/AttackNotifyInterface.h"

void UAttackComboAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    if (MeshComp && MeshComp->GetOwner())
    {
        IAttackNotifyInterface* CombatActor = Cast<IAttackNotifyInterface>(MeshComp->GetOwner());
        if (CombatActor != nullptr)
        {
            // 창을 열어줌과 동시에, 다음 목적지 섹션 이름까지 묶어서 원격 전송!
            CombatActor->SetComboWindowRegistry(true);

        }
    }

}

void UAttackComboAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAttackComboAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    if (MeshComp && MeshComp->GetOwner())
    {
        IAttackNotifyInterface* CombatActor = Cast<IAttackNotifyInterface>(MeshComp->GetOwner());
        if (CombatActor != nullptr)
        {
            // 콤보 입력 취소

            CombatActor->SetComboWindowRegistry(false);


        }
    }
}
