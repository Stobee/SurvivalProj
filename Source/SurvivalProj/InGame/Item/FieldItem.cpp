// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SurvivalProj/InGame/Player/PlayerCharacter.h"


// Sets default values
AFieldItem::AFieldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetCollisionProfileName(TEXT("ItemSearch"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Box);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->bRenderCustomDepth = false;

}

void AFieldItem::SetMeshOutlineActive(bool bActive)
{
	if (StaticMesh == nullptr) return;

	StaticMesh->bRenderCustomDepth = bActive;
	// 렌더 쓰레드 새로고침 강제화 하는 명령어
	StaticMesh->MarkRenderStateDirty();
}


void AFieldItem::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || OtherActor == this) return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		if (PlayerCharacter->IsLocallyControlled())
		{
			SetMeshOutlineActive(true);
		}
	}
}

void AFieldItem::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr || OtherActor == this) return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		if (PlayerCharacter->IsLocallyControlled())
		{
			SetMeshOutlineActive(false);
		}
	}
}

void AFieldItem::StartInteract_Implementation(AActor* InteractCauser) 
{
	if (!InteractCauser) return;
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(InteractCauser);
	bool SaveSuccess = PlayerCharacter->GetFieldItem(ItemID, ItemQuantity, ItemType);
	
	if (SaveSuccess)
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void AFieldItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (Box)
	{
		Box->OnComponentBeginOverlap.AddDynamic(this, &AFieldItem::OnBoxBeginOverlap);
		Box->OnComponentEndOverlap.AddDynamic(this, &AFieldItem::OnBoxEndOverlap);
	}
}

// Called every frame
void AFieldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

