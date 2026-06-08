// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldItem.generated.h"


class UBoxComponent;
class UStaticMeshComponent;


UCLASS()
class SURVIVALPROJ_API AFieldItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemState")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemState")
	int32 ItemQuantity = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
