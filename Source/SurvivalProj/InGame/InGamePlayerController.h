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

	// 서버용 컨트롤러 할당
	virtual void OnPossess(APawn* aPawn) override;

	// 클라이언트용 컨트롤러 할당
	virtual void AcknowledgePossession(APawn* InPawn) override;

	virtual void OnUnPossess() override;
};
