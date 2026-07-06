// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/MainCharacter.h"
#include "Golem.generated.h"

class UAnimMontage;
class UAIController;
class UBehaviorTree;

UENUM(BlueprintType)
enum class EGolemState : uint8
{
	Idle,
	Attacking,
	Stunned,
	Dead
};

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AGolem : public AMainCharacter
{
	GENERATED_BODY()

public:

	UBehaviorTree* GetBTAsset() { return GolemBehaviorTree; }
	UFUNCTION(BlueprintCallable, Category = "AI|Order")
	void OrderComboAttack();

	UFUNCTION(BlueprintCallable, Category = "AI|Order")
	void OrderJumpAttack();

	UFUNCTION(BlueprintCallable, Category = "AI|Order")
	void OrderRoaring();

	UFUNCTION(BlueprintCallable, Category = "AI|Order")
	void OrderStunned();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	
	AGolem();

	EGolemState CurrentState = EGolemState::Idle;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> GolemBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ComboAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> JumpAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> RoaringMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> KneelDownMontage;
};
