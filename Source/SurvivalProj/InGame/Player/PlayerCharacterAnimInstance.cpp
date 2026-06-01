// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Player = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
}

void UPlayerCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSecond)
{
	if (Player)
	{
		Speed = Player->GetVelocity().Length();
		
	}

}
