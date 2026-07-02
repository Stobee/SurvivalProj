// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

class AMainCharacter;
class UHPBarWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALPROJ_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP, BlueprintReadOnly, Category = "Attributes")
	float CurrentHP = 0.0f;

	UPROPERTY(ReplicatedUsing = OnRep_bIsDead, BlueprintReadOnly, Category = "Attributes")
	bool bIsDead = false;

	UPROPERTY()
	float MaxHP = 0.0f;

	UPROPERTY()
	float CurrentAttackPoint = 0.0f;

	UPROPERTY()
	float CurrentDefencePoint = 0.0f;

	UPROPERTY(Transient)
	TObjectPtr<AMainCharacter> OwnerCharacter = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UHPBarWidget> HPWidgt = nullptr;

// OnRep ÇÔ¼ö
	UFUNCTION()
	void OnRep_CurrentHP(float OldHP);

	UFUNCTION()
	void OnRep_bIsDead();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
