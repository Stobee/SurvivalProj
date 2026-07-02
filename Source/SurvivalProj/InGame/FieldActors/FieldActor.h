// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/FieldItem.h"
#include "FieldActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCharacterStatComponent;

UCLASS()
class SURVIVALPROJ_API AFieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldActor();

	void SetDamage(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> FieldActorMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "StatComp", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatComponent> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float MaxHp = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float CurrentHp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float ActorDef = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	int32 DropItemQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	FName DropItemId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	EItemType DropItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FieldActor|Data")
	TSubclassOf<AFieldItem> DropItemClass;

	bool DropItems();

	float SetOnFloor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
