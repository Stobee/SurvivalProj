// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "SurvivalProj/InGame/Components/TopDownSpringArmComponent.h"
#include "SurvivalProj/InGame/Components/PlayerInventoryComponent.h"
#include "SurvivalProj/InGame/Components/PlayerEquipmentComponent.h"
#include "SurvivalProj/InGame/Interfaces/InteractiveInterface.h"
#include "SurvivalProj/MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
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
	SkeletalMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	Inventory = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Inventory"));
	Equipment = CreateDefaultSubobject<UPlayerEquipmentComponent>(TEXT("Equipment"));
	
	// 나중에 횡스크롤 카메라로 바꾸는 로직 들어가야함
	SpringArm = CreateDefaultSubobject<UTopDownSpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    Camera->SetupAttachment(SpringArm);
    Camera->FieldOfView = 90.0f;
    Camera->ProjectionMode = ECameraProjectionMode::Perspective;
    Camera->bConstrainAspectRatio = false;
	
    
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			// 게임 시작 시 본인을 등록함
			GameMode->RegisterPlayer(this);
		}
	}

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOnAttackTrace)
	{
		ExecuteAttackTrace(TraceSocketName);
	}
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, WeaponEquipState);
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
		EIC->BindAction(IA_Inventory, ETriggerEvent::Started, this, &APlayerCharacter::OpenInventoryWidget);
		EIC->BindAction(IA_Evade, ETriggerEvent::Triggered, this, &APlayerCharacter::Evade);

		// 한 번만 입력되도록 Started 이벤트 적용
		EIC->BindAction(IA_UseItemSlot1, ETriggerEvent::Started, this, &APlayerCharacter::Input_UseSlot1);
		EIC->BindAction(IA_UseItemSlot2, ETriggerEvent::Started, this, &APlayerCharacter::Input_UseSlot2);
		EIC->BindAction(IA_UseItemSlot3, ETriggerEvent::Started, this, &APlayerCharacter::Input_UseSlot3);
		EIC->BindAction(IA_UseItemSlot4, ETriggerEvent::Started, this, &APlayerCharacter::Input_UseSlot4);
		EIC->BindAction(IA_UseItemSlot5, ETriggerEvent::Started, this, &APlayerCharacter::Input_UseSlot5);
			
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


void APlayerCharacter::MulticastPlayEquipWeaponMontage_Implementation()
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
		if (ActState == EPlayerActState::Attack || ActState == EPlayerActState::UsingInventory)
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

void APlayerCharacter::Evade()
{
	if (IsLocallyControlled())
	{
		ServerEvade();
	}
}

void APlayerCharacter::ServerEvade_Implementation()
{
	MulticastEvade();
}

void APlayerCharacter::MulticastEvade_Implementation()
{
	
	if (EvadeNormalMontage)
	{
		PlayAnimMontage(EvadeNormalMontage, 1.0f, TEXT("EvadeStart"));
		
	}
}

void APlayerCharacter::Zoom(FInputActionValue const& Value)
{
	float WheelValue = Value.Get<float>();

	SpringArm->AddTargetArmLength(-(WheelValue * ZoomWheelSpeed));
}

void APlayerCharacter::UseItemFromQuickSlot(uint8 KeyNum)
{
	if (ActState != EPlayerActState::Movable) return;
	switch (KeyNum)
	{
		case 1:
		{
			Inventory->UseItem((Inventory->GetInventorySize() - 1) + KeyNum);
		}
		break;

		case 2:
		{
			Inventory->UseItem((Inventory->GetInventorySize() - 1) + KeyNum);
		}
		break;
		case 3:
		{
			Inventory->UseItem((Inventory->GetInventorySize() - 1) + KeyNum);
		}
		break;
		case 4:
		{
			Inventory->UseItem((Inventory->GetInventorySize() - 1) + KeyNum);
		}
		break;
		case 5:
		{
			Inventory->UseItem((Inventory->GetInventorySize() - 1) + KeyNum);
		}
		break;
	}
}

void APlayerCharacter::OpenInventoryWidget()
{
	if (!Inventory) return;
	Inventory->VisibleInventoryWidget();
	
}


void APlayerCharacter::SetComboWindowRegistry(bool bIsOpen)
{
	bCanUseCombo = bIsOpen;

}

void APlayerCharacter::SetCharacterAttackEnd()
{
	if (ActState == EPlayerActState::Attack)
	{
		ActState = EPlayerActState::Movable;
		AttackComboState = 0;
	}
}

void APlayerCharacter::SetAttackTraceActive(bool bActive)
{
	AlreadyHitActors.Empty();
	bIsOnAttackTrace = bActive;

	if (AttackComboState == 2)
	{
		SetSocketName(TEXT("S_Right_Foot"));
	}
	else if (AttackComboState == 1)
	{
		SetSocketName(TEXT("S_Left_Hand"));
	}
	else
	{
		SetSocketName(TEXT("S_Weapon_r"));
	}
}

void APlayerCharacter::ExecuteAttackTrace(FName SocketName)
{
	// 캐릭터 널 가드
	if (GetMesh() == nullptr) return;

	switch (WeaponEquipState)
	{
	case (EWeaponEquipState::Unarmed):
	{
		if (SocketName == NAME_None) return;

		FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);
		
		UE_LOG(LogTemp, Log, TEXT("Current Active Socket Name: %s"), *SocketName.ToString());

		// 멀티 트레이스에 Hit된 액터를 담을 배열
		TArray<FHitResult> OutHits;

		// 무시할 액터 배열
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);


		// 근접 공격 채널 ECC_GameTraceChannel1
		bool bIsHit = UKismetSystemLibrary::SphereTraceMulti(this, SocketLocation, SocketLocation + (GetActorForwardVector() * 1.0f), 30.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false,
			ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

		if (bIsHit)
		{
			for (const FHitResult& Hit : OutHits)
			{

				AActor* HitActor = Hit.GetActor();
				if (HitActor != nullptr)
				{
					if (AlreadyHitActors.Contains(HitActor))
					{
						continue;
					}

					AlreadyHitActors.Add(HitActor);
					if (IsLocallyControlled())
					{
						ServerApplyDamage(HitActor, Hit);
					}

				}
			}
		}
		break;
		}
	case (EWeaponEquipState::OneHanded) :
	{
		FVector SocketLocation = Equipment->GetEquipWeaponActorSocketLocation();

		TArray<FHitResult> OutHits;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		bool bIsHit = UKismetSystemLibrary::SphereTraceMulti(this, SocketLocation, SocketLocation, 40.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false,
			ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

		if (bIsHit)
		{
			for (const FHitResult& Hit : OutHits)
			{

				AActor* HitActor = Hit.GetActor();
				if (HitActor != nullptr)
				{
					if (AlreadyHitActors.Contains(HitActor))
					{
						continue;
					}

					AlreadyHitActors.Add(HitActor);
					if (IsLocallyControlled())
					{
						ServerApplyDamage(HitActor, Hit);
					}

				}
			}
		}
		break;
	}
	case (EWeaponEquipState::TwoHanded) :
	{
		FVector SocketLocation;
		if (AttackComboState == 1)
		{
			SocketLocation = Equipment->GetEquipWeaponActorSocketLocation(true);
		}
		else
		{
			SocketLocation = Equipment->GetEquipWeaponActorSocketLocation();
		}

		TArray<FHitResult> OutHits;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		bool bIsHit = UKismetSystemLibrary::SphereTraceMulti(this, SocketLocation, SocketLocation, 40.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false,
			ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

		if (bIsHit)
		{
			for (const FHitResult& Hit : OutHits)
			{

				AActor* HitActor = Hit.GetActor();
				if (HitActor != nullptr)
				{
					if (AlreadyHitActors.Contains(HitActor))
					{
						continue;
					}

					AlreadyHitActors.Add(HitActor);
					if (IsLocallyControlled())
					{
						ServerApplyDamage(HitActor, Hit);
					}

				}
			}
		}
		break;
	}
	}
}

void APlayerCharacter::ServerApplyDamage_Implementation(AActor* TargetActor, const FHitResult& HitResult)
{
	if (TargetActor == nullptr || TargetActor->IsPendingKillPending()) return;

	if (!HasAuthority()) return;

	FVector ClientHitLocation = HitResult.ImpactPoint;
	FVector MyLocation = GetActorLocation();

	// 내 몸 중심점부터 클라이언트가 주장하는 타격 지점까지의 직선거리를 산출
	float TraceDistance = FVector::Dist(MyLocation, ClientHitLocation);

	if (TraceDistance > 100.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT(" [서버 트레이스 변조 감지]: 사거리 밖 유령 좌표 타격을 요청하여 기각함."));
		return;
	}

	UGameplayStatics::ApplyPointDamage(
		TargetActor,
		1.0f,
		ClientHitLocation,
		HitResult,
		GetController(),
		this,
		UDamageType::StaticClass()
	);
}

void APlayerCharacter::ClearHitRegistry()
{
}

void APlayerCharacter::SetPlayerOnInvincible(bool bIsOn)
{
	SetCanBeDamaged(bIsOn);
}



bool APlayerCharacter::GetFieldItem(const FItemSlotData& SlotData)
{
	if (Inventory->bIsQuickSlotFull())
	{
		if (Inventory->bIsInventorySlotFull()) return false;
		switch (SlotData.ItemType)
		{
		case (EItemType::Armor):
		{
			Inventory->RegisterArmorToEmptySlot(SlotData);
		} break;
		case (EItemType::Weapon):
		{
			Inventory->RegisterWeaponToEmptySlot(SlotData);
		} break;
		case (EItemType::Resource):
		{
			Inventory->RegisterResourceToEmptySlot(SlotData);
		} break;
		case (EItemType::Potion):
		{
			Inventory->RegisterPotionToEmptySlot(SlotData);
		} break;
		}
	}
	else
	{
		switch (SlotData.ItemType)
		{
		case (EItemType::Armor):
		{
			Inventory->RegisterArmorToEmptySlot(SlotData, true);
		} break;
		case (EItemType::Weapon):
		{
			Inventory->RegisterWeaponToEmptySlot(SlotData, true);
		} break;
		case (EItemType::Resource):
		{
			Inventory->RegisterResourceToEmptySlot(SlotData, true);
		} break;
		case (EItemType::Potion):
		{
			Inventory->RegisterPotionToEmptySlot(SlotData, true);

		} break;
		}
	}
	return true;
}

void APlayerCharacter::MoveItem(FItemSlotData SlotData, bool bTargetIsQuickSlot)
{
	ServerMoveItem(SlotData, bTargetIsQuickSlot);
}


void APlayerCharacter::ServerMoveItem_Implementation(FItemSlotData SlotData, bool bTargetIsQuickSlot)
{
	if (!HasAuthority())return;

	if (!bTargetIsQuickSlot)
	{
		// 퀵슬롯에 등록
		if (!Inventory->bIsQuickSlotFull())
		{
			bool TaskCompleted = false;
			switch (SlotData.ItemType)
			{
			case (EItemType::Armor):
			{
				TaskCompleted = Inventory->RegisterArmorToEmptySlot(SlotData, true);
			} break;
			case (EItemType::Weapon):
			{
				TaskCompleted = Inventory->RegisterWeaponToEmptySlot(SlotData, true);
			} break;
			case (EItemType::Resource):
			{
				TaskCompleted = Inventory->RegisterResourceToEmptySlot(SlotData, true);
			} break;
			case (EItemType::Potion):
			{
				TaskCompleted = Inventory->RegisterPotionToEmptySlot(SlotData, true);
			} break;
			}

			if (TaskCompleted)
			{
				Inventory->RemoveSlotItem(SlotData.SlotNumber);
			}
		}
		else
		{
			// 변경 실패 시 위젯 출력
			return;
		}
	}
	else
	{
		// 퀵슬롯 해제
		if (!Inventory->bIsInventorySlotFull())
		{
			bool TaskCompleted = false;
			switch (SlotData.ItemType)
			{
			case (EItemType::Armor):
			{
				TaskCompleted = Inventory->RegisterArmorToEmptySlot(SlotData);
			} break;
			case (EItemType::Weapon):
			{
				TaskCompleted = Inventory->RegisterWeaponToEmptySlot(SlotData);
			} break;
			case (EItemType::Resource):
			{
				TaskCompleted = Inventory->RegisterResourceToEmptySlot(SlotData);
			} break;
			case (EItemType::Potion):
			{
				TaskCompleted = Inventory->RegisterPotionToEmptySlot(SlotData);
			} break;
			}

			if (TaskCompleted)
			{
				Inventory->RemoveSlotItem(SlotData.SlotNumber);
			}
		}
		
	}
}

void APlayerCharacter::UseItem(int32 SlotNum)
{
	ServerUseItem(SlotNum);
}

void APlayerCharacter::ServerUseItem_Implementation(int32 SlotNum)
{
	if (!HasAuthority()) return;

	Inventory->UseItem(SlotNum);
}

void APlayerCharacter::DropItem(int32 SlotNum)
{
	ServerDropItem(SlotNum);
}

void APlayerCharacter::ServerDropItem_Implementation(int32 SlotNum)
{
	if (!HasAuthority()) return;

	FVector DropLocation = GetActorLocation() + (GetActorForwardVector() * 150.0f);

	DropLocation.Z = SetOnFloor();

	bool TaskCompleted = false;

	
	TaskCompleted = Inventory->DropItem(SlotNum, DropLocation);

	if (TaskCompleted)
	{
		Inventory->RemoveSlotItem(SlotNum);
	}
	
}

float APlayerCharacter::SetOnFloor()
{
	FVector TraceStart = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
	// 끝점: 캐릭터 고도에서 지하 바닥을 향해 500.0f 유닛만큼 레이저를 길게 사출
	FVector TraceEnd = GetActorLocation() + FVector(0.0f, 0.0f, -500.0f);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.bTraceComplex = true;
	TraceParams.AddIgnoredActor(this); // 나 자신은 검문 제외


	bool bHitGround = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, TraceParams);

	if (bHitGround)
	{
		// 레이저가 지형 바닥에 닿은 정확한 3D 임팩트 좌표 수령
		return HitResult.Location.Z;
	}

	// 레이저가 맞지 않으면 액터 위치
	return GetActorLocation().Z;
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
