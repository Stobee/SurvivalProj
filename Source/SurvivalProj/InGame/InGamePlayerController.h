// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"


class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;
};
