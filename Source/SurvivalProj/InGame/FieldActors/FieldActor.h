// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/Item/FieldItem.h"
#include "FieldActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCharacterStatComponent;
class UWidgetComponent;
class UHPBarWidget;

UCLASS()
class SURVIVALPROJ_API AFieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetDamage(float Damage);

	void HPBarUpdate();

	float GetMaxHp() { return MaxHp; }

	float GetDefPoint() { return ActorDef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser
	) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> FieldActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> HPWidget;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatComponent> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorState")
	float MaxHp = 10.0f;

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

	UPROPERTY(Transient)
	TObjectPtr<UHPBarWidget> HPBarWidget;

	bool bIsShaking = false;

	float ShakeTimer = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FX|Shake")
	float ShakeDuration = 0.25f; // Èçµé¸± ÃÑ ½Ã°£

	UPROPERTY(EditDefaultsOnly, Category = "FX|Shake")
	float ShakeFrequency = 50.0f; // Èçµé¸² ¼Óµµ (ÁÖÆÄ¼ö)

	UPROPERTY(EditDefaultsOnly, Category = "FX|Shake")
	float ShakeAmplitude = 15.0f; // Èçµé¸² ¹Ý°æ (ÇÈ¼¿/¼¾Æ¼¹ÌÅÍ)

	UPROPERTY(ReplicatedUsing = OnRep_bIsAttacked)
	bool bIsAttacked = false;

	UFUNCTION()
	void OnRep_bIsAttacked();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
