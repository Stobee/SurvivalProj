// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSecond) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSecond) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ref")
	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	bool bIsFalling = false;
	
};
