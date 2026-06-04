// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurvivalProj/Data/Enums/EPlayerActState.h"
#include "AttackNotifyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackNotifyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALPROJ_API IAttackNotifyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// 콤보 입력 가능 여부를 플레이어 캐릭터에게 전달
	virtual void SetComboWindowRegistry(bool bIsOpen) = 0;

	// 공격 종료 시 캐릭터의 콤보 관련 변수 초기화
	virtual void SetCharacterAttackEnd() = 0;

	// 맨손 또는 단검 등
	virtual void ExecuteShortAttackTrace() = 0;

	// 범위가 넓은 노티파이 스테이트용
	virtual void ClearHitRegistry() = 0;
};
