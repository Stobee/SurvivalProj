// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "SurvivalProj/InGame/MainCharacter.h"
#include "PlayerCharacter.generated.h"

class UTopDownSpringArmComponent;
class UCameraComponent;
class UInputAction;

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
	
public:
	
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(FInputActionValue const& Value);
	

protected:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "SpringArm", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTopDownSpringArmComponent>SpringArm;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent>Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

};
