// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/TopDownSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->bUseControllerDesiredRotation = false;
	bUseControllerRotationYaw = false;
	
	SpringArm = CreateDefaultSubobject<UTopDownSpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    Camera->SetupAttachment(SpringArm);
    Camera->FieldOfView = 90.0f;
    Camera->ProjectionMode = ECameraProjectionMode::Perspective;
    Camera->bConstrainAspectRatio = false;
    
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EIC)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &APlayerCharacter::StopJumping);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
	}
}

void APlayerCharacter::Move(FInputActionValue const& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y); // W/S 키
	AddMovementInput(RightDirection, MovementVector.X);  // A/D 키

	// [횡스크롤 로직] 전후 이동(W/S)은 무시하고 오직 월드 고정 평면의 좌우로만 가속
			// 프로젝트 설정에 맞춰 정형화된 좌우 방향 벡터(예: Y축 기동 시 FVector(0,1,0))를 직접 조준
	//const FVector SideDirection = FVector(0.0f, 1.0f, 0.0f);

	// MovementVector.X에는 IMC_SideScroll에서 매핑한 좌우 하드웨어 입력값 상주
	//AddMovementInput(SideDirection, MovementVector.X);
}
