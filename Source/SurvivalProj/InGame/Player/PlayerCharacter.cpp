// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/TopDownSpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->bUseControllerDesiredRotation = false;
	bUseControllerRotationYaw = false;
	
	// 나중에 횡스크롤 카메라로 바꾸는 로직 들어가야함
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
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::JumpWithAnim);
		EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &APlayerCharacter::StopJumping);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
		EIC->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &APlayerCharacter::Zoom);
		EIC->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
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

void APlayerCharacter::Attack()
{

	if (AttackComboState == 0)
	{
		if (ActState == EPlayerActState::Attack)
		{
			return;
		}
		ActState = EPlayerActState::Attack;

		bCanUseCombo = false;
		ServerAttack(TEXT("Attack1"));
		AttackComboState = 1;
		return;
	}

	if (AttackComboState != 0 && bCanUseCombo)
	{
		bCanUseCombo = false;
		
		FName NextAttackSection = NAME_None;
		if (AttackComboState == 1)
		{
			NextAttackSection = TEXT("Attack2");
			AttackComboState = 2; // 타수 전진
		}
		else if (AttackComboState == 2)
		{
			NextAttackSection = TEXT("Attack3");
			AttackComboState = 3; // 막타 전진
		}
		if (NextAttackSection != NAME_None)
		{
			ServerAttack(NextAttackSection);
		}
	}
}
void APlayerCharacter::ServerAttack_Implementation(FName SectionName)
{
	if (HasAuthority())
	{
		
		MulticastAttack(SectionName);
	}
}

void APlayerCharacter::MulticastAttack_Implementation(FName SectionName)
{
	
	if (UnarmedAttackMontage != nullptr)
	{
		PlayAnimMontage(UnarmedAttackMontage, 1.0f, SectionName);
	}
}

void APlayerCharacter::JumpWithAnim()
{
	Jump();
	ServerJumpWithAnim();
}

void APlayerCharacter::ServerJumpWithAnim_Implementation()
{
	if (HasAuthority())
	{
		MulticastJumpWithAnim();
	}
}

void APlayerCharacter::MulticastJumpWithAnim_Implementation()
{

	if (JumpStartMontage != nullptr)
	{
		PlayAnimMontage(JumpStartMontage, 1.0f);
	}
}

void APlayerCharacter::Zoom(FInputActionValue const& Value)
{
	float WheelValue = Value.Get<float>();

	SpringArm->AddTargetArmLength(-(WheelValue * ZoomWheelSpeed));
}

void APlayerCharacter::SetComboWindowRegistry(bool bIsOpen)
{
	bCanUseCombo = bIsOpen;

}

void APlayerCharacter::SetCharacterAttackEnd()
{
	ActState = EPlayerActState::Movable;
	AttackComboState = 0;
}

void APlayerCharacter::ExecuteShortAttackTrace()
{
	if (!HasAuthority()) return;

	
	if (GetMesh() == nullptr) return;

	// 캐릭터 전방 1미터 지정
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (GetActorForwardVector() * 100.0f);

	// 멀티 트레이스에 Hit된 액터를 담을 배열
	TArray<FHitResult> OutHits;

	// 무시할 액터 배열
	TArray<AActor*> ActorsToIgnore;


	// 단 1프레임 순간의 물리 공간 스윕 수색, 근접 공격 채널 ECC_GameTraceChannel1
	bool bIsHit = UKismetSystemLibrary::SphereTraceMulti(this, StartLocation, EndLocation,30.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),false,
		ActorsToIgnore,EDrawDebugTrace::ForDuration, OutHits,true);

	if (bIsHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor != nullptr)
			{
				// [무결성 노선] 단발성이므로 중복 체크 배열 수색 없이 즉시 데미지 주입 마감!
				UGameplayStatics::ApplyDamage(HitActor, 5, GetController(), this, UDamageType::StaticClass());

				
			}
		}
	}
}

void APlayerCharacter::ClearHitRegistry()
{
}
