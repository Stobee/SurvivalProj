// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEquipWeapon::AEquipWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->SetCollisionObjectType(ECC_GameTraceChannel1);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Capsule);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AEquipWeapon::SetWeaponCollisionActivate(bool bActivate)
{
	if (bActivate)
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void AEquipWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

