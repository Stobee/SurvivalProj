// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalProj/InGame/FieldActors/FieldActor.h"
#include "SurvivalProj/InGame/Item/ItemInstance.h"
#include "FieldItemBox.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AFieldItemBox : public AFieldActor
{
	GENERATED_BODY()
	
public:

	AFieldItemBox();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(Replicated)
	TArray<UItemInstance*> ItemSlots;
};
