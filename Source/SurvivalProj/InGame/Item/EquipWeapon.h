// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipWeapon.generated.h"


class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class SURVIVALPROJ_API AEquipWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipWeapon();

	void SetWeaponCollisionActivate(bool bActivate);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
