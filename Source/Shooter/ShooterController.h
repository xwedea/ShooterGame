// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.f;
	FTimerHandle RestartTimerHandle;


	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;
	

};
