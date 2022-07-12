// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float AxisVal);
	void MoveRight(float AxisVal);
	void LookUp_Controller(float AxisVal);
	void LookRight_Controller(float AxisVal);

private:
	UPROPERTY(EditAnywhere, Category="Gameplay")
		float CameraRotationRate{60};

	UPROPERTY(EditDefaultsOnly, Category="Combat")
		TSubclassOf<class AGun> GunClass;
	UPROPERTY()
		class AGun * Gun;

	void Shoot();


};
