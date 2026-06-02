// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownSpringArmComponent.h"

UTopDownSpringArmComponent::UTopDownSpringArmComponent()
{
    this->TargetArmLength = 600.0f;
    this->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    this->bInheritPitch = false;
    this->bInheritRoll = false;
    this->bInheritYaw = false;
    this->bUsePawnControlRotation = false;
    this->bEnableCameraLag = true;
    this->CameraLagSpeed = 3.0f;

    
}

void UTopDownSpringArmComponent::AddTargetArmLength(float value)
{
    if (this->TargetArmLength + value > 400.0f and this->TargetArmLength + value < 850.0f)
    {
        this->TargetArmLength = this->TargetArmLength + value;
    }
}



