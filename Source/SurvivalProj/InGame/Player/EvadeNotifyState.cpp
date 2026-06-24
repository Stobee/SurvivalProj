// Fill out your copyright notice in the Description page of Project Settings.


#include "EvadeNotifyState.h"
#include "SurvivalProj/InGame/Interfaces/EvadeInterface.h"

void UEvadeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    if (MeshComp && MeshComp->GetOwner())
    {
        if (MeshComp->GetOwner()->HasAuthority())
        {
            IEvadeInterface* EvadeActor = Cast<IEvadeInterface>(MeshComp->GetOwner());
            if (EvadeActor != nullptr)
            {

                EvadeActor->SetPlayerOnInvincible(true);

            }
        }
    }
}

void UEvadeNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UEvadeNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr) return;

    if (MeshComp && MeshComp->GetOwner())
    {
        if (MeshComp->GetOwner()->HasAuthority())
        {
            IEvadeInterface* EvadeActor = Cast<IEvadeInterface>(MeshComp->GetOwner());
            if (EvadeActor != nullptr)
            {
                EvadeActor->SetPlayerOnInvincible(false);

            }
        }
    }
}
