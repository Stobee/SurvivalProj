// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFieldActor::AFieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	FieldActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FieldActorMesh"));
	FieldActorMesh->SetupAttachment(Box);

	Stats = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stats"));
	

}

void AFieldActor::SetDamage(float Damage)
{
	CurrentHp -= Damage;

	if (CurrentHp <= 0)
	{
		bool TaskCompleted = DropItems();

		if (TaskCompleted)
		{
			TearOff();

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AFieldActor::BeginPlay()
{
	Super::BeginPlay();


	bool TaskCompleted = DropItems();

}

bool AFieldActor::DropItems()
{
	if (DropItemClass == nullptr || DropItemId == NAME_None || DropItemType == EItemType::None) return false;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return false; 

	DropItemQuantity = FMath::RandRange(1, 5);

	FVector SpawnLocation = GetActorLocation(); // 액터의 바닥 기준 지정

	

	for (int i = 0; i < DropItemQuantity; i++)
	{
		// 원점(SpawnLocation) 기준으로 반경 100유닛 이내의 '안전한 바닥 네비메쉬 좌표'를 수색!
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

		//FVector FinalDropLocation = SetOnFloor(); // 액터의 바닥 기준 지정

		//DropFieldItem->SetActorLocation(FinalDropLocation);

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

// Called every frame
void AFieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

