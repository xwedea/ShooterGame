// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn * KilledPawn)
{
	Super::PawnKilled(KilledPawn);


	// Player Dies
	APlayerController * PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if (PlayerController) {
		PlayerController->GameHasEnded(nullptr, false);
	}

	// AI Controller Dies


}



