// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALPROJ_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void RegisterPlayer(APlayerCharacter* Player);

	TArray<APlayerCharacter*> GetPlayers() { return Players; }
	
protected:

	TArray<APlayerCharacter*> Players;
};
