// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UE_LOG(LogTemp, Display, TEXT("Game Has Ended"));

	UUserWidget * LoseScreenWidget = CreateWidget(this, LoseScreenClass, "LoseScreen");
	if (LoseScreenWidget) {
		LoseScreenWidget->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}
