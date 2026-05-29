// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "TopDownSpringArmComponent.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API UTopDownSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	
protected:
	UTopDownSpringArmComponent();

	virtual void Activate(bool bReset = false) override;

	virtual void Deactivate() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent>Camera;
};
