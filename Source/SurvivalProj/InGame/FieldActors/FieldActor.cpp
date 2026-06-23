// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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
	

}

// Called when the game starts or when spawned
void AFieldActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

