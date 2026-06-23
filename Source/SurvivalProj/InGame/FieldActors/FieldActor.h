// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class SURVIVALPROJ_API AFieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> FieldActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float MaxHp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float CurrentHp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float ActorDef = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	int32 DropItemQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FieldActor|Data")
	TSubclassOf<AActor> DropItemClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
