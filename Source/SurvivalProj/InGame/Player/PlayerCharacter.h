// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "SurvivalProj/InGame/Interfaces/AttackNotifyInterface.h"
#include "SurvivalProj/InGame/MainCharacter.h"
#include "SurvivalProj/Data/Enums/EPlayerActState.h"
#include "PlayerCharacter.generated.h"

class UTopDownSpringArmComponent;
class UCameraComponent;
class UInputAction;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API APlayerCharacter : public AMainCharacter, public IAttackNotifyInterface
{
	GENERATED_BODY()
	
public:
	// 플레이어 생성자
	APlayerCharacter();

	// 플레이어 인풋
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 이동 로직
	void Move(FInputActionValue const& Value);

	// 점프 시작 시 몽타주 실행
	void JumpWithAnim();

	UFUNCTION(Server, Reliable)
	void ServerJumpWithAnim();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastJumpWithAnim();

	void Attack();

	UFUNCTION(Server, Reliable)
	void ServerAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttack();

	// 휠로 카메라 거리 조절
	void Zoom(FInputActionValue const& Value);

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bCanUseCombo = false;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FName NextAttackSection = TEXT("Attack1");

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	EPlayerActState ActState = EPlayerActState::Movable;

	// 인터페이스 함수
	virtual void SetComboWindowRegistry(bool bIsOpen, FName NextSection) override;
	

protected:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "SpringArm", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTopDownSpringArmComponent>SpringArm;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent>Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Zoom;

	// 줌 가속도. 에디터에서 조정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float ZoomWheelSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> JumpStartMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> UnarmedAttackMontage;
};
