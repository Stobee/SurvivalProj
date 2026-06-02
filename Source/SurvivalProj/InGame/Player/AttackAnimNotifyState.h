// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackAnimNotifyState.generated.h"

class FString;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
    // 💡 네이티브 노티파이 스테이트의 3대 마스터 인터페이스 오버라이드
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

    

    UPROPERTY(EditAnywhere, Category = "Combo Data")
    FName TargetSectionName = TEXT("Attack1");
    
    
};
