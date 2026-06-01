// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "TopDownSpringArmComponent.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UTopDownSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

protected:
	UTopDownSpringArmComponent();

	void AddTargetArmLength(float value);
	
};
