// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

void AMainGameMode::RegisterPlayer(APlayerCharacter* Player)
{
	if (Players.Contains(Player))
	{
		return;
	}

	Players.Add(Player);
}
