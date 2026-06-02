// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"
#include "EnhancedInputSubsystems.h"

void AInGamePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (IsLocalPlayerController() && GetLocalPlayer() != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(IMC_Default, 0);

		}
	}
}

void AInGamePlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	if (IsLocalPlayerController() && GetLocalPlayer() != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(IMC_Default, 0);

		}
	}

}

void AInGamePlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->ClearAllMappings();


		}
	}
}
