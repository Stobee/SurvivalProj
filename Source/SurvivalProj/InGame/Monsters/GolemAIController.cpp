// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SurvivalProj/InGame/Monsters/Golem.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"

AGolemAIController::AGolemAIController()
{
	bWantsPlayerState = true;
}

void AGolemAIController::OnPossess(APawn* InPawn)
{
	if (!HasAuthority()) return;

	AGolem* Golem = Cast<AGolem>(InPawn);

	if (Golem)
	{
		UBehaviorTree* BTAsset = Golem->GetBTAsset();

		if (BTAsset)
		{
			RunBehaviorTree(BTAsset);

			
		}
	}
}
