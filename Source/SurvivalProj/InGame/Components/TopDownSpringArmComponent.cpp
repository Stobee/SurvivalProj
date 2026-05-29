// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownSpringArmComponent.h"
#include "Camera/CameraComponent.h"

UTopDownSpringArmComponent::UTopDownSpringArmComponent()
{
    this->TargetArmLength = 800.0f;
    this->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    this->bInheritPitch = false;
    this->bInheritRoll = false;
    this->bInheritYaw = false;
    this->bUsePawnControlRotation = false;
    this->bEnableCameraLag = true;
    this->CameraLagSpeed = 3.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    
    if (Camera)
    {
        Camera->SetupAttachment(this, USpringArmComponent::SocketName);
        Camera->FieldOfView = 90.0f;
        Camera->ProjectionMode = ECameraProjectionMode::Perspective;
        Camera->bConstrainAspectRatio = false;
    }
}

void UTopDownSpringArmComponent::Activate(bool bReset)
{
    Super::Activate(bReset);
    
    if (Camera)
    {
        Camera->Activate(bReset);
    }
}

void UTopDownSpringArmComponent::Deactivate()
{
    Super::Deactivate();

    if (Camera)
    {
        Camera->Activate();
    }
}

