// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GolemAIController.generated.h"



/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AGolemAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AGolemAIController();

protected:

	virtual void OnPossess(APawn* InPawn) override;

};
