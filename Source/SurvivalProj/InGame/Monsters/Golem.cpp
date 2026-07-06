// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem.h"
#include "SurvivalProj/InGame/Monsters/GolemAIController.h"

void AGolem::OrderComboAttack()
{
}

void AGolem::OrderJumpAttack()
{
}

void AGolem::OrderRoaring()
{
}

void AGolem::OrderStunned()
{
}

float AGolem::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

AGolem::AGolem()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = AGolemAIController::StaticClass();
}
