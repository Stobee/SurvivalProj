// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/TopDownSpringArmComponent.h"
#include "SurvivalProj/InGame/Components/PlayerQuickSlotComponent.h"
#include "SurvivalProj/InGame/Components/PlayerInventoryComponent.h"
#include "SurvivalProj/InGame/Interfaces/InteractiveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->bUseControllerDesiredRotation = false;
	bUseControllerRotationYaw = false;

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	//Capsule->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
	Capsule->SetGenerateOverlapEvents(true);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleEndOverlap);

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	

	Inventory = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Inventory"));
	QuickSlot = CreateDefaultSubobject<UPlayerQuickSlotComponent>(TEXT("QuickSlot"));
	
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
		EIC->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EIC->BindAction(IA_UseItemSlot1, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_UseSlot1);
		EIC->BindAction(IA_UseItemSlot2, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_UseSlot2);
		EIC->BindAction(IA_UseItemSlot3, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_UseSlot3);
		EIC->BindAction(IA_UseItemSlot4, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_UseSlot4);
		EIC->BindAction(IA_UseItemSlot5, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_UseSlot5);
			
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

void APlayerCharacter::Interact()
{
	if (OverlappedActor)
	{
		ServerInteract(OverlappedActor);
	}

}

void APlayerCharacter::ServerInteract_Implementation(AActor* TargetActor)
{
	if (TargetActor == nullptr) return;

	if (TargetActor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
	{
	
		IInteractiveInterface::Execute_StartInteract(TargetActor, this);
		OverlappedActor = nullptr;
		
	}
}

void APlayerCharacter::MulticastInteract_Implementation(AActor* TargetActor)
{
	
}

void APlayerCharacter::EquipWeapon(FName WeaponName)
{
	ServerEquipWeapon(WeaponName);
}

void APlayerCharacter::ServerEquipWeapon_Implementation(FName WeaponName)
{
	if (HasAuthority())
	{
		MulticastEquipWeapon(WeaponName);
	}
}

void APlayerCharacter::MulticastEquipWeapon_Implementation(FName WeaponName)
{
	if (WeaponEquipMontage != nullptr)
	{
		PlayAnimMontage(WeaponEquipMontage, 1.0f);
	}
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

// 최종적으로 몽타주 실행
void APlayerCharacter::MulticastAttack_Implementation(FName SectionName)
{
	
	switch (WeaponEquipState)
	{
		case (EWeaponEquipState::Unarmed):
		{
			if (UnarmedAttackMontage != nullptr)
			{
				PlayAnimMontage(UnarmedAttackMontage, 1.0f, SectionName);
			}
		}
		break;

		case (EWeaponEquipState::OneHanded):
		{
			if (OneHandedAttackMontage != nullptr)
			{
				PlayAnimMontage(OneHandedAttackMontage, 1.0f, SectionName);
			}
		}
		break;

		case (EWeaponEquipState::TwoHanded):
		{
			if (TwoHandedAttackMontage != nullptr)
			{
				PlayAnimMontage(TwoHandedAttackMontage, 1.0f, SectionName);
			}
		}
		break;
	}
}

void APlayerCharacter::JumpWithAnim()
{
	if (ActState == EPlayerActState::Movable && GetCharacterMovement()->IsFalling() == false)
	{
		Jump();
		ServerJumpWithAnim();
	}
}

void APlayerCharacter::ServerJumpWithAnim_Implementation()
{
	if (HasAuthority())
	{
		MulticastJumpWithAnim();
	}
}

// 최종적으로 몽타주 실행
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

void APlayerCharacter::UseItemFromQuickSlot(uint8 KeyNum)
{
	switch (KeyNum)
	{
		case 1:
		{
			QuickSlot->ExecuteSlotAction(1);
		}
		break;

		case 2:
		{
			QuickSlot->ExecuteSlotAction(2);
		}
		break;
		case 3:
		{
			QuickSlot->ExecuteSlotAction(3);
		}
		break;
		case 4:
		{
			QuickSlot->ExecuteSlotAction(4);
		}
		break;
		case 5:
		{
			QuickSlot->ExecuteSlotAction(5);
		}
		break;
	}
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
	// 서버 가드
	if (!HasAuthority()) return;

	// 캐릭터 널 가드
	if (GetMesh() == nullptr) return;

	// 캐릭터 전방 1미터 지정
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (GetActorForwardVector() * 100.0f);

	// 멀티 트레이스에 Hit된 액터를 담을 배열
	TArray<FHitResult> OutHits;

	// 무시할 액터 배열
	TArray<AActor*> ActorsToIgnore;


	// 근접 공격 채널 ECC_GameTraceChannel1
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

//void APlayerCharacter::StartInteract_Implementation(AActor* InteractCauser) const
//{
//}

bool APlayerCharacter::GetFieldItem(FName ItemId, int32 ItemQuantity, EItemType ItemType)
{
	if (QuickSlot->bIsQuickSlotFull())
	{
		if (Inventory->bIsInventorySlotFull()) return false;
		switch (ItemType)
		{
		case (EItemType::Armor):
		{

		} break;
		case (EItemType::Weapon):
		{
			
		} break;
		case (EItemType::Resource):
		{

		} break;
		case (EItemType::Potion):
		{

		} break;
		}
	}
	else
	{
		switch (ItemType)
		{
		case (EItemType::Armor):
		{
			QuickSlot->RegisterArmorToEmptySlot(ItemId);
		} break;
		case (EItemType::Weapon):
		{
			QuickSlot->RegisterWeaponToEmptySlot(ItemId);
		} break;
		case (EItemType::Resource):
		{
			QuickSlot->RegisterResourceToEmptySlot(ItemId, ItemQuantity);
		} break;
		case (EItemType::Potion):
		{
			QuickSlot->RegisterPotionToEmptySlot(ItemId, ItemQuantity);
		} break;
		}
	}
	return true;
}

void APlayerCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || OtherActor == this) return;

	if (IsLocallyControlled() == false) return;

	IInteractiveInterface* InteractiveObject = Cast<IInteractiveInterface>(OtherActor);

	if (InteractiveObject)
	{
		OverlappedActor = OtherActor;
		
	}
}

void APlayerCharacter::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr || OtherActor == this) return;

	if (IsLocallyControlled() == false) return;

	IInteractiveInterface* InteractiveObject = Cast<IInteractiveInterface>(OtherActor);

	if (InteractiveObject)
	{
		OverlappedActor = nullptr;
		
	}
}
