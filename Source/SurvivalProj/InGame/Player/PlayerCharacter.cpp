// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/TopDownSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->bUseControllerDesiredRotation = false;
	
	SpringArm = CreateDefaultSubobject<UTopDownSpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
}
