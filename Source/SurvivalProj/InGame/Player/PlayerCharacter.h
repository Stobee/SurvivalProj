// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "SurvivalProj/InGame/Interfaces/AttackNotifyInterface.h"
#include "SurvivalProj/InGame/MainCharacter.h"
#include "SurvivalProj/Data/Enums/EPlayerActState.h"
#include "SurvivalProj/Data/Enums/EWeaponEquipState.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "PlayerCharacter.generated.h"

class UTopDownSpringArmComponent;
class UCameraComponent;
class UPlayerInventoryComponent;
class UPlayerQuickSlotComponent;
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
	void ServerAttack(FName SectionName);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttack(FName SectionName);

	void EquipWeapon(FName WeaponName);

	UFUNCTION(Server, Reliable)
	void ServerEquipWeapon(FName WeaponName);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEquipWeapon(FName WeaponName);

	void Interact();

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* TargetActor);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastInteract(AActor* TargetActor);

	// 휠로 카메라 거리 조절
	void Zoom(FInputActionValue const& Value);

	// 숫자 키로 입력한 인벤토리의 아이템 사용
	void UseItemFromQuickSlot(uint8 KeyNum);

	// 공격 콤보 입력 활성화 여부
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bCanUseCombo = false;

	// 이동 가능 여부와 관련된 상태
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	EPlayerActState ActState = EPlayerActState::Movable;

	// 현재 공격 콤보 단계
	UPROPERTY(BluePrintReadOnly, Category = "Input")
	uint8 AttackComboState = 0;

	// 무기 장착 상태
	UPROPERTY(BluePrintReadOnly, Category = "Input")
	EWeaponEquipState WeaponEquipState = EWeaponEquipState::Unarmed;

	// 필드 아이템과 상호작용 시 호출
	bool GetFieldItem(FName ItemId, int32 ItemQuantity, EItemType ItemType);


	UFUNCTION()
	void OnCapsuleBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnCapsuleEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	// 현재 오버랩 된 액터
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	AActor* OverlappedActor = nullptr;

	// 인터페이스 함수
	// set bCanUseCombo
	virtual void SetComboWindowRegistry(bool bIsOpen) override;

	// set ActState Movable
	virtual void SetCharacterAttackEnd() override;

	// use sphere multiTrace by AnimNotify
	virtual void ExecuteShortAttackTrace() override;

	// reset Hit Actors
	virtual void ClearHitRegistry() override;

	// Interact Other Actors
	//virtual void StartInteract_Implementation(AActor* InteractCauser) const override;
	
private:

	void Input_UseSlot1() { UseItemFromQuickSlot(1); }
	void Input_UseSlot2() { UseItemFromQuickSlot(2); }
	void Input_UseSlot3() { UseItemFromQuickSlot(3); }
	void Input_UseSlot4() { UseItemFromQuickSlot(4); }
	void Input_UseSlot5() { UseItemFromQuickSlot(5); }
	
// 컴포넌트
protected:

	// 탑 다운 전용 스프링 암
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTopDownSpringArmComponent>SpringArm;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent>Camera;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerInventoryComponent>Inventory;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerQuickSlotComponent>QuickSlot;

// Input
protected:

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_UseItemSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_UseItemSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_UseItemSlot3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_UseItemSlot4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_UseItemSlot5;

// 애니메이션 몽타주
protected:

	// 에디터에서 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> JumpStartMontage;

	// 에디터에서 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> UnarmedAttackMontage;

	// 에디터에서 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> OneHandedAttackMontage;

	// 에디터에서 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> TwoHandedAttackMontage;

	// 에디터에서 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> WeaponEquipMontage;
};
