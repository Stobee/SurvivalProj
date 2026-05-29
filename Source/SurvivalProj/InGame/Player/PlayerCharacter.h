// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/MainCharacter.h"
#include "PlayerCharacter.generated.h"

class UTopDownSpringArmComponent;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
	
public:
	
	APlayerCharacter();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "SpringArm", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTopDownSpringArmComponent>SpringArm;
};
