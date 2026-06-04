// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollSpringArmComponent.h"

USideScrollSpringArmComponent::USideScrollSpringArmComponent()
{
    this->TargetArmLength = 700.0f;
    this->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    this->bInheritPitch = false;
    this->bInheritRoll = false;
    this->bInheritYaw = false;
    this->bUsePawnControlRotation = false;
    this->bEnableCameraLag = true;
    this->CameraLagSpeed = 3.0f;
    this->bDoCollisionTest = false;


}
