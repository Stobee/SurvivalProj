// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "SurvivalProj/InGame/Components/CharacterStatComponent.h"
#include "SurvivalProj/InGame/Widgets/HPBarWidget.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFieldActor::AFieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	FieldActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FieldActorMesh"));
	FieldActorMesh->SetupAttachment(Box);

	HPWidget = CreateDefaultSubobject<UWidgetComponent>((TEXT("HPWidget")));
	HPWidget->SetupAttachment(Box);

	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPWidget->SetDrawSize(FVector2D(150.f, 30.f));
	HPWidget->AddRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	HPWidget->SetVisibility(false);
	

	Stats = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stats"));
	

}

void AFieldActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFieldActor, bIsAttacked);
}

void AFieldActor::SetDamage(float Damage)
{
	Stats->TakeDamage(Damage);

	bIsAttacked = true;

	// 서버의 OnRep 실행
	OnRep_bIsAttacked();

	if (Stats->GetIsDead())
	{
		bool TaskCompleted = DropItems();
		
		if (TaskCompleted)
		{
			TearOff();

			Destroy();
		}
	}
}

void AFieldActor::HPBarUpdate()
{
	if (HPBarWidget)
	{
		HPBarWidget->HPBarUpdate(Stats->GetMaxHP(), Stats->GetCurrentHP());
	}
}

// Called when the game starts or when spawned
void AFieldActor::BeginPlay()
{
	Super::BeginPlay();

	HPBarWidget = Cast<UHPBarWidget>(HPWidget->GetWidget());
	if (HPBarWidget)
	{
		HPBarUpdate();
	}

}

float AFieldActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority()) return 0.0f;

	// 내부 이벤트 방출을 위해 부모 함수 '격발' 자체는 무조건 해줘야 한다.
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDamage(DamageAmount);

	return DamageAmount;
}

bool AFieldActor::DropItems()
{
	if (DropItemClass == nullptr || DropItemId == NAME_None || DropItemType == EItemType::None) return false;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return false; 

	DropItemQuantity = FMath::RandRange(1, 3);

	FVector SpawnLocation = GetActorLocation(); // 액터의 바닥 기준 지정

	for (int i = 0; i < DropItemQuantity; i++)
	{
		FNavLocation NavResult;
		bool bFoundRandPoint = NavSys->GetRandomPointInNavigableRadius(SpawnLocation, 150.0f, NavResult);

		if (bFoundRandPoint)
		{
			SpawnLocation = NavResult.Location;
		}

		SpawnLocation.Z = SetOnFloor();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Owner = nullptr;

		AFieldItem* DropFieldItem = GetWorld()->SpawnActor<AFieldItem>(DropItemClass, SpawnLocation, FRotator(0.0f, FMath::RandRange(0.0f, 360.0f),0.0f), SpawnParams);

		FItemSlotData UpdatePacket;

		UpdatePacket.Quantity = 1;
		UpdatePacket.ItemId = DropItemId;
		UpdatePacket.ItemType = DropItemType;

		DropFieldItem->SetItemState(UpdatePacket);
	}

	return true;
}

float AFieldActor::SetOnFloor()
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

void AFieldActor::OnRep_bIsAttacked()
{
	HPWidget->SetVisibility(true);
	bIsShaking = true;
	ShakeTimer = ShakeDuration;
}

// Called every frame
void AFieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShaking)
	{
		ShakeTimer -= DeltaTime;
		if (ShakeTimer <= 0.0f)
		{
			bIsShaking = false;
			bIsAttacked = false;
			
			FieldActorMesh->SetRelativeLocation(FVector::ZeroVector);
		}
		else
		{
			// 시간에 따라 -1.0 ~ 1.0을 왕복하는 고속 진동축 연산
			float ShakeOffset = FMath::Sin(ShakeTimer * ShakeFrequency) * ShakeAmplitude;

			// 감쇠 효과(시간이 갈수록 진동이 약해짐) 추가
			ShakeOffset *= (ShakeTimer / ShakeDuration);

			// 좌우(Y축) 방향으로 메시를 정밀 격동 유발
			FieldActorMesh->SetRelativeLocation(FVector(0.0f, ShakeOffset, 0.0f));
		}
	}

}

