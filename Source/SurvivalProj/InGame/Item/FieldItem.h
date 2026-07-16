// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/Data/Enums/EItemType.h"
#include "SurvivalProj/InGame/Item/ItemWidgetStruct.h"
#include "SurvivalProj/InGame/Interfaces/InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "FieldItem.generated.h"


class UBoxComponent;
class UStaticMeshComponent;


UCLASS()
class SURVIVALPROJ_API AFieldItem : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldItem();

	void SetMeshOutlineActive(bool bActive);

	void SetItemState(const FItemSlotData& ItemStruct);

	EItemType GetItemType() { return ItemStateStruct.ItemType; }

	UFUNCTION() 
	void OnBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnBoxEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	// 인터페이스 함수
	virtual void StartInteract_Implementation(AActor* InteractCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemState")
	FItemSlotData ItemStateStruct;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
